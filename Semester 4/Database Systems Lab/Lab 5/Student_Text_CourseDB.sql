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
    foreign key (regno, course_id, sem) references enroll(regno, course_id, sem) -- Corrected foreign key
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
(547216, 'Operating Systems, Internal principles and design', 'Pearson', 'William Stallings')
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
