SET serveroutput ON

CREATE OR REPLACE TRIGGER accident_intimation
AFTER INSERT ON PARTICIPATED
FOR EACH ROW
DECLARE
    accident_count INT;
BEGIN
    -- Count the number of accidents the driver has participated in
    SELECT COUNT(*)
    INTO accident_count
    FROM PARTICIPATED
    WHERE driver_id = :NEW.driver_id;

    -- Check if the driver has participated in 2 accidents
    IF accident_count = 2 THEN
        -- Intimate the driver (printing a message in the DBMS_OUTPUT window for now)
        DBMS_OUTPUT.PUT_LINE('Driver ' || :NEW.driver_id || ' has been involved in 2 accidents. Please take caution!');
    END IF;
END;
/
