-- Create Tables
CREATE TABLE student(
    regno varchar(20),
    name varchar(50),
    major varchar(20),
    bdate date,
    primary key (regno)
);

CREATE TABLE course(
    course_id int,
    cname varchar(30),
    dept varchar(30),
    primary key (course_id)
);

CREATE TABLE enroll(
    regno varchar(20),
    course_id int,
    sem int,
    book_isbn int,
    primary key (regno, course_id, sem),
    foreign key (regno) references student,
    foreign key (course_id) references course
);

CREATE TABLE text(
    book_isbn int,
    book_title varchar(50),
    publisher varchar(50),
    author varchar(50),
    primary key (book_isbn)
);

CREATE TABLE book_adoption(
    course_id int,
    sem int,
    book_isbn int,
    regno varchar(20),
    primary key (course_id, sem, book_isbn),
    foreign key (course_id) references course,
    foreign key (book_isbn) references text,
    foreign key (regno, course_id, sem) references enroll(regno, course_id, sem)
);

-- Insert Data (Sample)
INSERT INTO text (book_isbn, book_title, publisher, author) VALUES 
(269593, 'Database System Concepts', 'Tata McGraw Hill', 'Abraham Silberschatz'),
(356329, 'Operating System Concepts', 'Wiley', 'Abraham Silberschatz'),
(969325, 'Introduction to Algorithms', 'MIT Press', 'CLRS'),
(333527, 'Data Communications and Networking', 'Tata McGraw Hill', 'Behrouz A Forouzan'),
(527468, 'TCP/IP Protocol Suite', 'Tata McGraw Hill', 'Behrouz A Forouzan'),
(438965, 'Cryptography and Network Security', 'Pearson', 'William Stallings'),
(636574, 'Data and Computer Communications', 'Pearson', 'William Stallings'),
(547216, 'Operating Systems, Internal principles and design', 'Pearson', 'William Stallings'),
(766359, 'Fundamentals of Data Structures', 'MIT Press', 'Sartaj Sahani'),
(666222, 'Algorithms C++', 'MIT Press', 'Sartaj Sahani');

INSERT INTO student (regno, name, major, bdate) VALUES 
('230953232', 'Abhidutta Mukund Giri', 'CCE', '2005-07-20'),
('230953241', 'Adriteyo Das', 'CCE', '2005-08-03'),
('230953212', 'Piyush', 'CSE', '2006-03-06'),
('220905698', 'Stavya Pandey', 'CSE', '2005-08-29'),
('240909562', 'Daksh Arora', 'DSE', '2006-07-05'),
('240973652', 'Sohini', 'DSE', '2007-01-02'),
('230911569', 'Kashvi Ranjan', 'IT', '2005-06-07'),
('230953092', 'Samhita Vishwanath', 'IT', '2004-12-02'),
('230959096', 'Alok Sharma', 'VLSI', '2004-01-02');

INSERT INTO COURSE (course_id, cname, dept) VALUES 
(2222, 'DAA', 'ICT'),
(2225, 'DBMS', 'ICT'),
(2252, 'CNP', 'ICT'),
(2122, 'DS', 'ICT'),
(2342, 'PDC', 'ICT'),
(2255, 'OS', 'ICT'),
(2253, 'ESD', 'ICT'),
(2174, 'SDT', 'ICT'),
(3222, 'DAA', 'CSE'),
(3252, 'OS', 'CSE'),
(3122, 'DS', 'CSE'),
(3695, 'QC', 'CSE'),
(3225, 'DBS', 'CSE'),
(4123, 'OS', 'VLSI'),
(4166, 'CNP', 'VLSI'),
(5179, 'DV', 'DSE'),
(5122, 'DS', 'DSE'),
(5164, 'DM', 'DSE'),
(5155, 'AP', 'DSE');

INSERT INTO ENROLL (regno, course_id, sem, book_isbn) VALUES 
    ('230953232', 2222, 4, 969325),
    ('230953092', 2222, 4, 969325),
    ('230911569', 2222, 5, 969325),
    ('230911569', 2253, 5, 438965),
    ('230911569', 5164, 5, 636574),
    ('240909562', 5122, 2, 636574),
    ('240909562', 5179, 4, 333527),
    ('240909562', 3695, 2, 969325),
    ('230959096', 4123, 4, 969325),
    ('240909562', 4166, 4, 969325),
    ('230953241', 2222, 4, 969325),
    ('230953212', 2225, 4, 969325);

INSERT INTO Book_adoption (course_id, sem, book_isbn, regno) VALUES 
    (2225, 4, 269593, '230953232'),
    (3225, 4, 269593, '230953092'),
    (2255, 4, 356329, '230911569'),
    (2255, 4, 547216, '230911569'),
    (3252, 4, 356329, '230911569'),
    (3252, 4, 547216, '230911569'),
    (4123, 4, 547216, '230959096'),
    (4123, 4, 636574, '230959096'),
    (2222, 4, 969325, '230953232');

