-- Create Tables
CREATE TABLE PERSON(
    driver_id VARCHAR(30), 
    name VARCHAR(50), 
    address VARCHAR(100), 
    PRIMARY KEY (driver_id)
);

CREATE TABLE CAR(
    regno VARCHAR(20), 
    model VARCHAR(30), 
    Years INT, 
    PRIMARY KEY (regno)
);

CREATE TABLE ACCIDENT(
    report_number INT PRIMARY KEY, 
    accd_date DATE, 
    location VARCHAR(50)
);

CREATE TABLE OWNS (
    driver_id VARCHAR(30), 
    regno VARCHAR(20), 
    PRIMARY KEY (driver_id, regno), 
    FOREIGN KEY (driver_id) REFERENCES PERSON(driver_id), 
    FOREIGN KEY (regno) REFERENCES CAR(regno)
);

CREATE TABLE PARTICIPATED (
    driver_id VARCHAR(30), 
    regno VARCHAR(20), 
    report_number INT, 
    damage_amount INT, 
    PRIMARY KEY (driver_id, regno, report_number), 
    FOREIGN KEY (driver_id) REFERENCES PERSON(driver_id), 
    FOREIGN KEY (regno) REFERENCES CAR(regno), 
    FOREIGN KEY (report_number) REFERENCES ACCIDENT (report_number)
);

-- Insert Data
INSERT INTO PERSON (driver_id, name, Address) VALUES 
('SLIMM308RPGDET','Marshall Mathers','8695, Bel Air Rd, Los Angeles, California- 632 788'),
('STRBY001CALA','Abel Tesfaye','9969, Hollywood Hills, Los Angeles, California- 632 705'),
('LJMNY690','Luigi Mangione','Brooklyn Heihts, Brooklyn, New York City, New York- 329 504'),
('EJTX09','Eric Johnson','East Dallas Rd, Texas County, Texas- 959 253'),
('WTBG001','Bill Gates','5695 Gates Manor, Seattle, Washington-777 653'),
('NMX017A','Walter White','308, Negro Arroyo Lane, Albuquerque, New Mexico'),
('KA33MLR1', 'Abhi M G', '3000, Blueberry Hills, Kadri, Mangalore'),
('MYS99KA05', 'Mike Ross', 'Springfield, Bejai New Road, Bangalore');

INSERT INTO CAR (regno, model, Years) VALUES 
('NY6BL8956', 'Chevrolet Corvette', 2007),
('CALA050', 'McLaren P1', 2017),
('CALA09', 'Miata', 2001),
('WT5698SEA7', 'Ford Cortina', 2007),
('TX89AU1', 'Ford F-150', 1996),
('CALA007', 'Toyota Supra', 1996),
('AMG999', 'Mercedes sls AMG', 2019),
('KA19MF5432', 'Maruti 800', 1994);

INSERT INTO OWNS (driver_id, regno) VALUES 
('LJMNY690', 'NY6BL8956'),
('STRBY001CALA', 'CALA050'),
('SLIMM308RPGDET', 'CALA09'),
('WTBG001', 'WT5698SEA7'),
('EJTX09', 'TX89AU1'),
('NMX017A', 'CALA007'),
('KA33MLR1', 'AMG999'),
('MYS99KA05', 'KA19MF5432');

INSERT INTO ACCIDENT (report_number, accd_date, location) VALUES 
(42, '2016-03-02', 'East Texas Highway'),
(13, '2005-07-02', 'Chicago Street'),
(562, '2001-09-29', 'Mexico Gate'),
(56, '2008-12-05', 'Brooklyn Bridge'),
(972, '2008-04-13', 'Park Avenue'),
(342, '2007-06-09', 'Alabama County Exit');

INSERT INTO PARTICIPATED (driver_id, regno, report_number, damage_amount) VALUES 
('WTBG001', 'WT5698SEA7', 42, 72000),
('LJMNY690', 'NY6BL8956', 42, 67000),
('EJTX09', 'TX89AU1', 13, 20000),
('STRBY001CALA', 'CALA050', 13, 12000),
('NMX017A', 'CALA007', 562, 6000),
('SLIMM308RPGDET', 'CALA09', 56, 4000),
('NMX017A', 'CALA007', 972, 6000),
('LJMNY690', 'NY6BL8956', 972, 6000),
('NMX017A', 'CALA007', 342, 2000),
('SLIMM308RPGDET', 'CALA09', 342, 700);
