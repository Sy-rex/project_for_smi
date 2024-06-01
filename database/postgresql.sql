/*----CREATE tables----*/

CREATE TABLE journal
(
	id SERIAL PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	year_of_foundation DATE,
	rating DECIMAL(3,1)
);

CREATE TABLE edition
(
	id SERIAL PRIMARY KEY,
	name VARCHAR(50) NOT NULL,
	main_editor VARCHAR(100),
	year_of_creation DATE,
	rating DECIMAL(3,1)
);

CREATE TABLE authors
(
	id SERIAL PRIMARY KEY,
	fullname VARCHAR(200) NOT NULL,
	edition_id INTEGER,
	rating DECIMAL(3,1),
	FOREIGN KEY (edition_id) REFERENCES edition (id)
);

CREATE TABLE article
(
	id SERIAL PRIMARY KEY,
	journal_id INTEGER,
	name VARCHAR(200),
	rating DECIMAL(3,1),
	description VARCHAR(300),
	price MONEY,
	release_date DATE,
	FOREIGN KEY (journal_id) REFERENCES journal (id)
);

CREATE TABLE article_authors
(
	article_id INTEGER,
	author_id INTEGER,
	PRIMARY KEY (article_id, author_id),
	FOREIGN KEY (article_id) REFERENCES article (id),
	FOREIGN KEY (author_id) REFERENCES authors (id)	
);

/*----TASK 3A----*/

SELECT 
    a.name,
    a.rating AS "Рейтинг статьи",
    j.rating AS "Рейтинг журнала",
    CASE
        WHEN a.rating > j.rating THEN 'Актуально'
        WHEN a.rating < j.rating THEN 'Не Актуально'
        ELSE 'Актуальна частично'
    END AS "Актуальность" 
FROM 
    article a
JOIN 
    journal j ON a.journal_id = j.id;

/*----TASK 3B----*/

CREATE VIEW merge_count_authors_for_article AS 
SELECT
	ar.name AS "Название статьи",
	ar.rating AS "Рейтинг статьи",
	ar.description AS "Описание",
	COUNT(aa.author_id) AS "Количество авторов в статье"
FROM article ar
JOIN
	article_authors aa ON ar.id = aa.article_id
JOIN
	authors au ON au.id = aa.author_id
GROUP BY ar.id,ar.name;

--TRIGGER FOR UPDATE VIEW--

CREATE OR REPLACE FUNCTION update_article_author_count()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE merge_count_authors_for_article
    SET "Количество авторов в статье" = (
        SELECT COUNT(*)
        FROM article_authors
        WHERE article_authors.article_id = NEW.id
    )
    WHERE "Название статьи" = NEW.name;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER update_article_author_count_trigger
INSTEAD OF INSERT OR UPDATE OR DELETE ON merge_count_authors_for_article
FOR EACH ROW
EXECUTE FUNCTION update_article_author_count();

/*----TASK 3C----*/

CREATE MATERIALIZED VIEW old_edition AS
SELECT 
    name AS "Название редакции", 
    year_of_foundation AS "Год основания", 
    rating AS "Рейтинг редакции"
FROM 
    journal
WHERE 
    EXTRACT(YEAR FROM CURRENT_DATE) - EXTRACT(YEAR FROM year_of_foundation) > 10;


/*----TASK 3D----*/

--SUBQUERY IN SELECT--

SELECT 
    name AS "Название статьи",
    rating AS "Рейтинг статьи",
    (SELECT name FROM journal WHERE id = article.journal_id) AS "Название журнала"
FROM 
    article;

--SUBQUERY IN FROM--

SELECT 
    a.id AS "ID статьи",
    a.name AS "Название статьи",
    au.fullname AS "Автор статьи"
FROM 
    article a
JOIN 
    (
        SELECT 
            aa.article_id,
            au.fullname
        FROM 
            article_authors aa
        JOIN 
            authors au ON aa.author_id = au.id
		WHERE
			au.rating > 8
    ) AS au ON a.id = au.article_id
GROUP BY 
    a.id, au.fullname, a.name;

--SUBQUERY IN WHERE--

SELECT
	*
FROM
	authors au
WHERE
	au.rating = (SELECT MAX(rating) FROM edition);

/*----TASK 3E----*/

SELECT 
	j.id AS "ID журнала",
	j.name AS "Название",
	(
		SELECT 
			SUM(a.price) 
		FROM 
			article a 
		WHERE 
			a.journal_id = j.id
	)
AS "Заработал журнал"
FROM journal j

--####################--

SELECT 
    j.id AS "ID журнала",
    j.name AS "Название",
    COUNT(a.id) AS "Кол-во статей в год основания журнала"
FROM 
    journal j
LEFT JOIN 
    article a ON j.id = a.journal_id AND EXTRACT(YEAR FROM a.release_date) = EXTRACT(YEAR FROM j.year_of_foundation)
GROUP BY 
    j.id, j.name;

--####################--

SELECT 
    au.fullname AS "Автор",
    edi.name AS "Название редакции"
FROM 
    authors au
JOIN 
    edition edi ON au.edition_id = edi.id
WHERE 
    au.fullname = edi.main_editor;
	
/*----TASK 3F----*/

SELECT 
    j.id AS "ID журнала",
    j.name AS "Название журнала",
    COUNT(a.id) AS "Количество статей",
    AVG(a.rating) AS "Средний рейтинг статей"
FROM 
    journal j
LEFT JOIN 
    article a ON j.id = a.journal_id
GROUP BY 
    j.id, j.name
HAVING 
    COUNT(a.id) > 5
ORDER BY 
    "Средний рейтинг статей" DESC;

/*----TASK 3G----*/

SELECT 
    au.fullname AS "Автор", 
    ar.name AS "Название статьи", 
    au.rating AS "Рейтинг автора"
FROM 
    authors au
JOIN 
    article_authors aa ON au.id = aa.author_id
JOIN 
    article ar ON aa.article_id = ar.id
WHERE 
    au.rating > ANY (SELECT rating FROM article);

SELECT 
	j.name AS "Название журнала",
	j.rating AS "Рейтинг журнала"
FROM journal j
WHERE
	j.rating > ALL (SELECT a.rating FROM article a WHERE a.journal_id = j.id);

/*----TASK 4----*/

-- btree индекс
CREATE INDEX idx_journal_name_btree ON journal USING btree (name);

-- функциональный индекс
CREATE INDEX idx_authors_name_lower ON authors (LOWER(fullname));

-- hash индекс
CREATE INDEX idx_article_rating_hash ON article USING hash (rating);

EXPLAIN ANALYZE SELECT * FROM journal WHERE name = 'Nature';

EXPLAIN ANALYZE SELECT * FROM authors WHERE LOWER(fullname) = 'Bob Brown';

EXPLAIN ANALYZE SELECT * FROM article WHERE rating = 9.8;

/*----TASK 5----*/
-- Триггеры для таблицы journal

CREATE TRIGGER olap_add_journal
AFTER INSERT OR UPDATE OR DELETE ON journal
FOR EACH ROW EXECUTE FUNCTION olap_add();

CREATE TRIGGER olap_add_article
AFTER INSERT OR UPDATE OR DELETE ON article
FOR EACH ROW EXECUTE FUNCTION olap_add();

CREATE TRIGGER olap_add_authors
AFTER INSERT OR UPDATE OR DELETE ON authors
FOR EACH ROW EXECUTE FUNCTION olap_add();

CREATE TRIGGER olap_add_edition
AFTER INSERT OR UPDATE OR DELETE ON edition
FOR EACH ROW EXECUTE FUNCTION olap_add();

CREATE TRIGGER olap_add_article_authors
AFTER INSERT OR UPDATE OR DELETE ON article_authors
FOR EACH ROW EXECUTE FUNCTION update_article_authors_counters();

/*----TASK 6----*/

CREATE OR REPLACE FUNCTION olap_add()
RETURNS TRIGGER AS $$
	BEGIN
	IF TG_OP = 'DELETE' THEN
		INSERT INTO olap (OperationType, TableName, Username, ChangedData)
		VALUES (TG_OP, TG_TABLE_NAME, current_user, row_to_json(OLD));
		RETURN OLD;
	ELSIF TG_OP = 'INSERT' OR TG_OP = 'UPDATE' THEN
		INSERT INTO olap (OperationType, TableName, Username, ChangedData)
		VALUES (TG_OP, TG_TABLE_NAME, current_user, row_to_json(NEW));
		RETURN NEW;
		END IF;
	RETURN NULL;
	END;
$$ LANGUAGE plpgsql;

-- Функция для тригера на изменения в таблице article_authors(счётчик операций)

CREATE OR REPLACE FUNCTION update_article_authors_counters() RETURNS TRIGGER AS $$
BEGIN
    IF TG_OP = 'INSERT' THEN
        UPDATE article_authors_statistics SET counter = counter + 1 WHERE operation = 'INSERT';
    ELSIF TG_OP = 'UPDATE' THEN
        UPDATE article_authors_statistics SET counter = counter + 1 WHERE operation = 'UPDATE';
    ELSIF TG_OP = 'DELETE' THEN
        UPDATE article_authors_statistics SET counter = counter + 1 WHERE operation = 'DELETE';
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TABLE article_authors_statistics (
    operation VARCHAR(10) PRIMARY KEY,
    counter INTEGER NOT NULL DEFAULT 0
);

INSERT INTO article_authors_statistics (operation, counter) VALUES
('INSERT', 0),
('UPDATE', 0),
('DELETE', 0);

/*----TASK 7----*/

-- journal

CREATE OR REPLACE PROCEDURE add_journal(
    IN journal_name VARCHAR(50),
    IN journal_year_of_foundation DATE,
    IN journal_rating DECIMAL(3, 1)
) AS $$
BEGIN
    INSERT INTO journal (name, year_of_foundation, rating)
    VALUES (journal_name, journal_year_of_foundation, journal_rating);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE delete_journal(
    IN journal_id INTEGER
) AS $$
BEGIN
    DELETE FROM journal WHERE id = journal_id;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE update_journal(
    IN journal_id INTEGER,
    IN journal_name VARCHAR(50),
    IN journal_year_of_foundation DATE,
    IN journal_rating DECIMAL(3, 1)
) AS $$
BEGIN
    UPDATE journal
    SET name = journal_name,
        year_of_foundation = journal_year_of_foundation,
        rating = journal_rating
    WHERE id = journal_id;
END;
$$ LANGUAGE plpgsql;

-- edition

CREATE OR REPLACE PROCEDURE add_edition(
    IN edition_name VARCHAR(50),
    IN edition_main_editor VARCHAR(100),
    IN edition_year_of_creation DATE,
    IN edition_rating DECIMAL(3, 1)
) AS $$
BEGIN
    INSERT INTO edition (name, main_editor, year_of_creation, rating)
    VALUES (edition_name, edition_main_editor, edition_year_of_creation, edition_rating);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE delete_edition(
    IN edition_id INTEGER
) AS $$
BEGIN
    DELETE FROM edition WHERE id = edition_id;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE update_edition(
    IN edition_id INTEGER,
    IN edition_name VARCHAR(50),
    IN edition_main_editor VARCHAR(100),
    IN edition_year_of_creation DATE,
    IN edition_rating DECIMAL(3, 1)
) AS $$
BEGIN
    UPDATE edition
    SET name = edition_name,
        main_editor = edition_main_editor,
        year_of_creation = edition_year_of_creation,
        rating = edition_rating
    WHERE id = edition_id;
END;
$$ LANGUAGE plpgsql;

-- authors

CREATE OR REPLACE PROCEDURE add_author(
    IN author_fullname VARCHAR(200),
    IN author_edition_id INTEGER,
    IN author_rating DECIMAL(3, 1)
) AS $$
BEGIN
    INSERT INTO authors (fullname, edition_id, rating)
    VALUES (author_fullname, author_edition_id, author_rating);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE delete_author(
    IN author_id INTEGER
) AS $$
BEGIN
    DELETE FROM authors WHERE id = author_id;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE update_author(
    IN author_id INTEGER,
    IN author_fullname VARCHAR(200),
    IN author_edition_id INTEGER,
    IN author_rating DECIMAL(3, 1)
) AS $$
BEGIN
    UPDATE authors
    SET fullname = author_fullname,
        edition_id = author_edition_id,
        rating = author_rating
    WHERE id = author_id;
END;
$$ LANGUAGE plpgsql;

-- article

CREATE OR REPLACE PROCEDURE add_article(
    IN article_journal_id INTEGER,
    IN article_name VARCHAR(200),
    IN article_rating DECIMAL(3, 1),
    IN article_description VARCHAR(300),
    IN article_price MONEY,
    IN article_release_date DATE
) AS $$
BEGIN
    INSERT INTO article (journal_id, name, rating, description, price, release_date)
    VALUES (article_journal_id, article_name, article_rating, article_description, article_price, article_release_date);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE delete_article(
    IN article_id INTEGER
) AS $$
BEGIN
    DELETE FROM article WHERE id = article_id;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE update_article(
    IN article_id INTEGER,
    IN article_journal_id INTEGER,
    IN article_name VARCHAR(200),
    IN article_rating DECIMAL(3, 1),
    IN article_description VARCHAR(300),
    IN article_price MONEY,
    IN article_release_date DATE
) AS $$
BEGIN
    UPDATE article
    SET journal_id = article_journal_id,
        name = article_name,
        rating = article_rating,
        description = article_description,
        price = article_price,
        release_date = article_release_date
    WHERE id = article_id;
END;
$$ LANGUAGE plpgsql;

-- article_authors

CREATE OR REPLACE PROCEDURE add_article_author(
    IN article_id INTEGER,
    IN author_id INTEGER
) AS $$
BEGIN
    INSERT INTO article_authors (article_id, author_id)
    VALUES (article_id, author_id);
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE delete_article_author(
    IN article_id INTEGER,
    IN author_id INTEGER
) AS $$
BEGIN
    DELETE FROM article_authors
    WHERE article_id = article_id AND author_id = author_id;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE update_article_author(
    IN old_article_id INTEGER,
    IN old_author_id INTEGER,
    IN new_article_id INTEGER,
    IN new_author_id INTEGER
) AS $$
BEGIN
    UPDATE article_authors
    SET article_id = new_article_id,
        author_id = new_author_id
    WHERE article_id = old_article_id AND author_id = old_author_id;
END;
$$ LANGUAGE plpgsql;

/*----TASK 8----*/

CREATE OR REPLACE PROCEDURE update_article_ratings_procedure(IN threshold DECIMAL(3, 1)) AS $$
DECLARE
    max_rating DECIMAL(3, 1);
    max_rating_count INTEGER;
BEGIN

    -- Вычисляем максимальный рейтинг статей
	
    SELECT MAX(rating) INTO max_rating FROM article;

    -- Вычисляем количество статей с максимальным рейтингом
	
    SELECT COUNT(*)
    INTO max_rating_count
    FROM article
    WHERE rating = max_rating;

    -- Проверяем, если есть более 10 статей с максимальным рейтингом
	
    IF max_rating_count > 10 THEN
        BEGIN
            -- Уменьшаем рейтинги всех статей на 10%
            UPDATE article SET rating = rating * 0.9;
            COMMIT;
        END;
    ELSE
        ROLLBACK;
    END IF;
END;
$$ LANGUAGE plpgsql;

/*----TASK 9----*/

CREATE OR REPLACE FUNCTION update_journal_ratings() RETURNS VOID AS $$
DECLARE
    -- Объявляем переменные для хранения данных из таблицы и для временных вычислений
    journal_row RECORD;
    calculated_rating DECIMAL(3, 1);
    current_year INTEGER;
BEGIN
    -- Получаем текущий год
    current_year := EXTRACT(YEAR FROM CURRENT_DATE);
    -- Открываем курсор для выбора данных из таблицы journal
    FOR journal_row IN SELECT id, rating, year_of_creation FROM journal LOOP
        -- Проверяем, совпадает ли год создания журнала с текущим годом
        IF EXTRACT(YEAR FROM journal_row.year_of_creation) = current_year THEN
            -- Если да, то умножаем текущий рейтинг на 1.1
            calculated_rating := journal_row.rating * 1.1;
        ELSE
            -- Если нет, то рейтинг понижаем в 0.95
            calculated_rating := journal_row.rating * 0.95;
        END IF;
        -- Обновляем значение рейтинга в таблице journal
        UPDATE journal
        SET rating = calculated_rating
        WHERE id = journal_row.id;
    END LOOP;
    -- Закрываем курсор
    CLOSE journal_row;
END;
$$ LANGUAGE plpgsql;

-- проверка

SELECT update_journal_ratings();

/*----TASK 10----*/

-- средний рейтинг авторов статьи

CREATE OR REPLACE FUNCTION article_authors_avg_rating(article_id INTEGER) RETURNS DECIMAL(3, 2) AS $$
DECLARE
    avg_rating DECIMAL(3, 2);
BEGIN
    SELECT AVG(au.rating)
    INTO avg_rating
    FROM authors au
    JOIN article_authors aa ON au.id = aa.author_id
    WHERE aa.article_id = article_id;

    RETURN COALESCE(avg_rating, 0);
END;
$$ LANGUAGE plpgsql;

-- возвращает авторов, которые являются редактором издания и ещё у него и у его редакции одинаковый рейтинг

CREATE OR REPLACE FUNCTION matched_authors_by_edition(edition_id INTEGER) RETURNS TABLE(author_name VARCHAR(200), author_rating DECIMAL(3, 1)) AS $$
BEGIN
    RETURN QUERY
    SELECT au.fullname, au.rating
    FROM authors au
    JOIN edition ed ON au.edition_id = ed.id
    WHERE au.edition_id = edition_id
    AND au.rating = ed.rating
    AND au.fullname = ed.main_editor;
END;
$$ LANGUAGE plpgsql;

/*----TASK 11----*/

CREATE ROLE reader_role;
GRANT SELECT ON ALL TABLES IN SCHEMA public TO reader_role;
ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES TO reader_role;

CREATE ROLE editor_role;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO editor_role;
ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT ALL PRIVILEGES ON TABLES TO editor_role;
GRANT ALL PRIVILEGES ON SCHEMA public TO editor_role;

CREATE USER reader_user WITH PASSWORD '12345';
GRANT reader_role TO reader_user;

CREATE USER editor_user WITH PASSWORD '12345';
GRANT editor_role TO editor_user;

/*----TASK 12----*/

CREATE TABLE olap (
Id_operation SERIAL PRIMARY KEY,
Timestamp TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
OperationType VARCHAR(50) NOT NULL,
TableName VARCHAR(255) NOT NULL,
Username TEXT,
ChangedData TEXT
);
	

/*----TEST INSERT AND DROP TABLE----*/

-- Добавление данных в таблицу journal
INSERT INTO journal (name, year_of_foundation, rating)
VALUES ('Vogue Russia', '1987-01-01', 9.1),
	('RusInvest', '2022-03-05', 5.7),
	('University', '2013-03-02', 6.2),
	('Fisher', '2024-01-01',7.8),
	('Kinopoisk', '2016-09-25', 4.9),
	('Twitch FM','2024-05-22', 2.3),
	('Русский спорт', '2005-03-28', 5.5),
	('Секреты звезд', '1999-01-01', 7.8),
	('Тайны вселенной', '2005-06-15', 8.5),
	('Поваренная книга', '2010-03-12', 6.9),
	('Загадки истории', '1997-07-21', 9.2),
	('Киномания', '2001-11-30', 8.0),
	('Смех без правил', '2004-09-14', 7.4),
	('Техномир', '2013-02-20', 8.6),
	('Журнал мод', '2000-05-05', 9.1),
	('Винные истории', '2012-08-19', 7.5),
	('Путешествия во времени', '2003-12-25', 8.7),
	('Авто легенды', '2009-04-07', 7.8),
	('Музыкальные вибрации', '2015-06-30', 8.9),
	('Фитнес и здоровье', '2016-10-10', 7.6),
	('Наука популярно', '2007-01-15', 8.3),
	('Психология каждого', '2011-09-09', 9.0),
	('Сад и огород', '2018-03-03', 7.2),
	('Любителям природы', '2014-05-05', 8.4),
	('Искусство жить', '2017-07-07', 7.9),
	('Правдивые новости', '2002-10-20', 8.1),
	('Книга рекордов', '2008-08-18', 7.3),
	('Ретро автомобили', '2019-11-11', 8.8),
	('Космос как он есть', '2010-12-12', 9.4),
	('Мир аниме', '2006-03-15', 7.7),
	('Гурман', '2013-07-07', 8.5),
	('Животный мир', '2005-02-02', 7.8),
	('Игры разума', '2011-11-11', 8.6),
	('Электроника для всех', '2014-09-09', 9.1),
	('Любимые сериалы', '2012-04-04', 7.4),
	('Загадки мифологии', '2008-10-10', 8.7),
	('Хоррор гид', '2017-12-12', 9.0);

-- Добавление данных в таблицу edition
INSERT INTO edition (name, main_editor, year_of_creation, rating)
VALUES ('Writers original', 'Максим Петров', '2012-03-15', 9),
	('Rus-Writer', 'Олег Монгол', '2016-05-02', 7.8),
	('Investment', 'Василий Корчагин', '2022-01-01', 6.3),
	('Man edition', 'Григорий Полунин', '2023-05-27', 5.2),
	('KPictures', 'Кирилл Ольховец', '2019-04-13', 7.9),
	('89 SQUAD', 'Владимир Братишкин', '2018-06-12', 8.9),
	('Match TV', 'Георгий Черданцев', '2010-08-08', 5.9),
	('Мода без границ', 'Александр Васильев', '2010-01-01', 8.6),
	('Экстремальные виды спорта', 'Эвелин Солт', '2006-06-06', 7.7),
	('Мир робототехники', 'Иван Иванов', '2014-03-03', 9.2),
	('Секреты здоровья', 'Мария Семенова', '2009-07-07', 8.5),
	('Финансы для всех', 'Дмитрий Денисов', '2012-12-12', 7.6),
	('Правда о космосе', 'Сергей Петров', '2008-08-08', 8.8),
	('Наш домашний питомец', 'Екатерина Роза', '2011-11-11', 9.1),
	('Путешествуй легко', 'Антон Коробков', '2013-05-05', 8.7),
	('Мир вкусной еды', 'Гордон Рамзи', '2015-02-02', 8.9),
	('Стартапы и инновации', 'Илон Маск', '2017-09-09', 9.3),
	('Полезные советы', 'Ольга Петрова', '2018-10-10', 8.1),
	('Уголок крафта', 'Марина Белова', '2016-01-01', 7.8),
	('Эксперименты дома', 'Николай Николаев', '2019-03-03', 8.4),
	('Поэзия и проза', 'Лариса Рубальская', '2005-04-04', 7.9),
	('Домашняя аптека', 'Анна Хилькевич', '2007-07-07', 8.3),
	('Строим и ремонтируем', 'Андрей Малахов', '2011-08-08', 8.2),
	('Истории успеха', 'Опра Уинфри', '2003-09-09', 9.0),
	('Музыкальный бокс', 'Тимур Родригез', '2002-06-06', 7.6),
	('За кадром', 'Сергей Безруков', '2004-05-05', 8.5),
	('Программирование с нуля', 'Марк Зукерберг', '2006-03-03', 9.4),
	('КиноПоиск HD', 'Юрий Дудь', '2010-10-10', 7.8),
	('Кулинария от шефа', 'Антон Исаков', '2012-02-02', 8.7),
	('Журнал для родителей', 'Ксения Собчак', '2014-12-12', 8.0),
	('Все о рыбалке', 'Иван Затевахин', '2016-08-08', 7.5),
	('Автомир', 'Джереми Кларксон', '2018-04-04', 9.2),
	('Литературные обзоры', 'Борис Акунин', '2017-11-11', 8.6),
	('Научные открытия', 'Михаил Варшавский', '2015-03-03', 9.1),
	('Советы психолога', 'Юлия Латынина', '2013-07-07', 8.4),
	('Туристический журнал', 'Андрей Бедняков', '2011-09-09', 8.9),
	('Гаджетомания', 'Алексей Навальный', '2019-05-05', 9.0);


-- Добавление данных в таблицу authors
INSERT INTO authors (fullname, edition_id, rating)
VALUES ('Максим Петров', 1, 9),
	('Михаил Васильков', 2, 5.6),
	('Василий Корчагин', 3, 7.4),
	('Григорий Полунин', 4, 5.2),
	('Никита Быстриков', 4, 4.2),
	('Степан Пропастин', 5, 7.9),
	('Евгений Порсев', 5, 8.1),
	('Илья Мазелов', 6, 6.7),
	('Владимир Братишкин', 6, 8.9),
	('Андрей Аршавин', 7, 8.8),
	('Алексей Попов', 8, 7.7),
	('Мария Васильева', 9, 8.6),
	('Никита Джигурда', 10, 6.8),
	('Валентина Рубцова', 11, 9.1),
	('Сергей Жуков', 12, 7.9),
	('Анастасия Ивлеева', 13, 8.3),
	('Гарик Харламов', 14, 9.2),
	('Павел Воля', 15, 7.4),
	('Ольга Бузова', 16, 6.5),
	('Ксения Собчак', 17, 8.1),
	('Иван Ургант', 18, 9.3),
	('Дмитрий Нагиев', 19, 8.4),
	('Елена Малышева', 20, 7.8),
	('Владимир Познер', 21, 9.0),
	('Сергей Светлаков', 22, 7.5),
	('Тимур Батрутдинов', 23, 8.7),
	('Михаил Галустян', 24, 8.9),
	('Александр Петров', 25, 9.1),
	('Светлана Ходченкова', 26, 8.0),
	('Ян Гордиенко', 27, 7.6),
	('Денис Косяков', 28, 8.8),
	('Анна Хилькевич', 29, 7.7),
	('Виктория Боня', 30, 8.9),
	('Юрий Дудь', 31, 9.2),
	('Илья Прусикин', 32, 8.3),
	('Лиза Анохина', 33, 8.6),
	('Антон Лапенко', 34, 7.8),
	('Кирилл Терешин', 35, 6.4),
	('Алексей Щербаков', 36, 7.5),
	('Диана Шурыгина', 37, 8.2);
	

-- Добавление данных в таблицу article
INSERT INTO article (journal_id, name, rating, description, price, release_date)
VALUES (1, 'Ирина Шейк покаряет мир', 8.3, 'Модель снова лидирует на подиуме в Париже', 10.99, '2012-04-01'),
	(3, 'МИРЭА лучший университет', 7.4, 'Студенты МИРЭА выиграли в хакатоне', 8.78, '2013-03-02'),
	(2, 'Акции Лукойла растут', 8.1, 'Изменилась дивидендная политика компании', 9.43, '2022-09-08'),
	(1, 'Кара Делевинь снова на подиуме', 6.9, 'Актриса появилась на показе в Милане', 8.56, '2024-04-02'),
	(1, 'Аня Рубик снова блондинка', 9.1, 'Модели изменила цвет волос после Испании', 9.22, '2015-06-24'),
	(1, 'Синди Кроуфорд бьёт рекорды', 9.4, 'Девушка за месяц поменяла 1000 платьев', 8.34, '2017-08-12'),
	(1, 'Лара Стоун снова на высоте', 7.6, 'Модель покарила гору Эверест', 6.87, '2019-05-27'),
	(4, 'Всё о судаке', 5.2, 'Всё о том как поймать судака осенью', 3.2, '2024-03-02'),
	(5, 'Марго Робби стала режиссёром', 9.9, 'Актриса основала свою компанию', 8.78, '2020-01-03'),
	(5, 'Натали Портман вышла замуж', 9.9, 'Натали осчастливила Евгения Пропастина', 8.78, '2020-02-03'),
	(5, 'Кира Найтли история величества', 9.9, 'Имя ей было дано благодаря Русским корням', 8.78, '2020-01-05'),
	(5, 'Эль Фэннинг - подарок судьбы', 9.9, 'Девушка подарила машину Никите Черенкову', 8.78, '2020-10-03'),
	(5, 'Морган Фриман стал скуфом', 9.9, 'Актёр выпил 10л пива в выходные', 8.78, '2020-01-03'),
	(5, 'Кристиан Бэйл перестал быть сигмой', 9.9, 'Актёр перестал делать отжимания', 8.78, '2021-01-03'),
	(5, 'Киллиан Мёрфи подрался в баре', 9.9, 'Актёр не поделился с Конором Макгрегором кириешками', 8.78, '2022-01-03'),
	(5, 'Роберт Дауни Мл. стал старшим', 9.9, 'Стал настоящим дауни', 8.78, '2020-07-03'),
	(5, 'Никита Кологривый очушпанился', 9.9, 'Актёр снялся в клипе в женском платье', 8.78, '2024-01-03'),
	(5, 'Александр Петров снова на экране', 9.9, 'Актер вызывает агрессию со стороны зрителей', 8.78, '2020-01-03'),
	(5, 'Денис Дорохов в кино', 9.9, 'Отличие от собаки никто не заметил', 8.78, '2020-01-03'),
	(6, 'Юрий Хованский стал дельфином', 3.3, 'Если б море было пивом', 3.34, '2024-01-03'),
	(6, 'Новый конфликт в Сербии', 3.3, 'Данила Горилла окупировал одноимённый ресторан', 5.33, '2024-01-03'),
	(6, 'Мэлстрой продал казино', 3.3, 'Условием сделки было побриться налысо', 3.33, '2017-04-23'),
	(6, 'Братишкин запустил стрим', 3.3, 'Компания VK забрала у него галочку', 4.33, '2024-01-03'),
	(7, 'Ну где же ваши ручки?', 9.6, 'Артём Дзюба выложил утреннюю зарядку', 7.52, '2022-01-06'),
	(7, 'Горы мышц слабеют', 8.4, 'Степан Клюшкин не пришёл в зал', 8.4, '2009-01-03'),
	(8, 'Инопланетяне открыли свой магазин пирожков на Земле', 8.4, 'История первого инопланетного фаст-фуда', 6.45, '2024-02-11'),
	(9, 'Диета на основе марсианской пыли: новый тренд', 8.6, 'Все, что нужно знать о космическом питании', 7.80, '2024-02-12'),
	(10, 'Почему утки могут управлять временем', 8.1, 'Научное объяснение необычных способностей уток', 9.00, '2024-02-13'),
	(11, 'Вампиры реальны: истории из первых уст', 9.3, 'Сборник свидетельств о встречах с вампирами', 7.00, '2024-02-14'),
	(12, 'Говорящие растения научились спорить', 7.9, 'Разговоры с флорой: что они думают о нас?', 8.20, '2024-02-15'),
	(13, 'Клоны Наполеона захватывают мир', 8.5, 'Как клоны исторической личности стремятся к власти', 9.70, '2024-02-16'),
	(14, 'Как медитация помогает видеть будущее', 9.2, 'Разгадка феномена предсказаний через медитацию', 8.50, '2024-02-17'),
	(15, 'Как избежать встречи с динозаврами в современном мире', 8.8, 'Практическое руководство по безопасности', 7.60, '2024-02-18'),
	(16, 'НЛО использовали мою кошку для связи с другими галактиками', 9.0, 'Личный рассказ о космических приключениях домашнего питомца', 1200, '2024-02-19'),
	(17, 'Секреты пирамид: что мы все еще не знаем', 8.6, 'Новые теории о назначении древних пирамид', 9.90, '2024-02-20'),
	(18, 'Бабушкин метод борьбы с интернет-троллями', 7.7, 'Традиционные подходы к современным проблемам', 8.35, '2024-02-21'),
	(19, 'Как я научился разговаривать с мебелью', 9.1, 'О необычных способностях и диалогах с предметами', 6.25, '2024-02-22'),
	(20, 'Котики как глобальное оружие массового умиления', 8.9, 'Влияние милых видео на мировую экономику', 8.75, '2024-02-23'),
	(21, 'Картофель из мультивселенной: новый вид питания', 9.2, 'Открытие параллельного мира, где картофель правит', 9.45, '2024-02-24'),
	(22, 'Роботы-пылесосы восстали против хозяев', 8.3, 'История бунта умных устройств в одном жилом комплексе', 8.20, '2024-02-25'),
	(23, 'Секреты успешных растений: как они добиваются успеха', 7.8, 'Исследование поведения высокопродуктивной флоры', 9.60, '2024-02-26'),
	(24, 'Почему морские свинки стали новыми лидерами интернета', 8.7, 'Повышенное внимание к морским свинкам как культурному феномену', 4.00, '2024-02-27'),
	(25, 'Акулы, которые любят пиццу: необычное открытие', 9.0, 'Исследования предпочтений акул в еде', 8.10, '2024-02-28'),
	(26, 'Путешествие во времени возможно: первые успешные эксперименты', 9.4, 'Отчет о революционных достижениях в физике', 7.50, '2024-02-29'),
	(27, 'Мифы о лунах: что мы не знаем о наших небесных телах', 8.8, 'Разоблачение популярных заблуждений о спутниках планет', 9.90, '2024-03-01'),
	(28, 'Параллельные миры: нашли ли мы своих двойников?', 8.5, 'Новые исследования в области квантовой физики', 8.50, '2024-03-02'),
	(29, 'Загадочные сигналы из глубин океана', 9.1, 'Новое открытие в морских исследованиях', 9.40, '2024-03-03'),
	(30, 'Суперспособности собак: миф или реальность?', 8.6, 'Научный взгляд на необычные таланты питомцев', 8.90, '2024-03-04'),
	(31, 'Чайные церемонии для кошек: новый тренд в Японии', 9.3, 'Как кошки стали главными гостями на традиционных японских мероприятиях', 2.00, '2024-03-05'),
	(32, 'Овощи, которые чувствуют: новые данные о перцепции растений', 7.9, 'Обзор последних исследований в ботанике', 8.10, '2024-03-06'),
	(33, 'Интервью с говорящей лошадью', 8.4, 'Эксклюзивное интервью с первой в мире лошадью, которая научилась разговаривать', 9.50, '2024-03-07'),
	(34, 'Гномы в саду: правда или миф?', 8.8, 'Расследование о том, живут ли в наших садах мифические существа', 9.90, '2024-03-08'),
	(35, 'Как музыка влияет на рост растений', 9.0, 'Научное исследование музыкальных предпочтений растений', 6.70, '2024-03-09'),
	(36, 'Приключения банана: анимационный сериал от фруктов', 8.7, 'Запуск первого в мире шоу, созданного фруктами', 8.80, '2024-03-10'),
	(37, 'Космические коты: как они завоевали Марс?', 9.3, 'Отчет о первых марсианских котах и их жизни на красной планете', 8.75, '2024-03-11');
	

-- Добавление данных в таблицу article_authors
INSERT INTO article_authors (article_id, author_id)
VALUES (1, 1),
	(2,1),
	(3,1),
	(4,1),
	(5,1),
	(6,1),
	(7,1),
	(2,2),
	(3,3),
	(8,4),
	(8,5),
	(9,6),
	(9,7),
	(10,6),
	(11,7),
	(12,6),
	(13,6),
	(13,7),
	(14,7),
	(15,6),
	(16,7),
	(17,6),
	(18,7),
	(19,6),
	(20,8),
	(20,9),
	(21,9),
	(22,8),
	(23,8),
	(23,9),
	(24,10),
	(25,10),
	(26,11),
	(27,12),
	(28,13),
	(29,14),
	(30,15),
	(31,16),
	(32,17),
	(33,18),
	(34,19),
	(35,20),
	(36,21),
	(37,22),
	(38,23),
	(39,24),
	(40,25),
	(41,26),
	(42,27),
	(43,28),
	(44,29),
	(45,30),
	(46,31),
	(47,32),
	(48,33),
	(49,34),
	(50,35),
	(51,36),
	(52,37),
	(53,38),
	(54,39),
	(55,40);

-- Удаление представления merge_count_authors_for_article
DROP VIEW IF EXISTS merge_count_authors_for_article;
DROP MATERIALIZED VIEW IF EXISTS old_edition;

-- Удаление внешнего ключа из таблицы article_authors
ALTER TABLE article_authors DROP CONSTRAINT IF EXISTS article_authors_article_id_fkey;
ALTER TABLE article_authors DROP CONSTRAINT IF EXISTS article_authors_author_id_fkey;

-- Удаление таблицы article_authors
DROP TABLE IF EXISTS article_authors;

-- Удаление оставшихся таблиц
DROP TABLE IF EXISTS article;
DROP TABLE IF EXISTS authors;
DROP TABLE IF EXISTS edition;
DROP TABLE IF EXISTS journal;


EXPLAIN ANALYZE
SELECT au.*
FROM authors au
JOIN edition e ON au.edition_id = e.id
WHERE LOWER(au.fullname) = 'Bob Breow' AND e.rating > 7.0;

EXPLAIN ANALYZE
SELECT j.*
FROM journal j	
JOIN article a ON j.id = a.journal_id
WHERE j.name = 'Nature' AND a.rating > 8.0;

EXPLAIN ANALYZE
SELECT a.*, j.*
FROM article a
JOIN journal j ON a.journal_id = j.id
WHERE a.rating = 9.5 AND j.rating > 8.0;













