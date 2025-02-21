set server output ON

CREATE OR REPLACE TRIGGER display_driver_info_before_insert
BEFORE INSERT ON PARTICIPATED
FOR EACH ROW
DECLARE
    driver_name VARCHAR2(50);
    driver_address VARCHAR2(100);
BEGIN
    -- Fetch driver information from the PERSON table
    SELECT name, address
    INTO driver_name, driver_address
    FROM PERSON
    WHERE driver_id = :NEW.driver_id;

    -- Output driver information (using DBMS_OUTPUT for display in Oracle)
    DBMS_OUTPUT.PUT_LINE('Driver Name: ' || driver_name);
    DBMS_OUTPUT.PUT_LINE('Driver Address: ' || driver_address);
END;
/
