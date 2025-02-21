SET serveroutput ON

CREATE OR REPLACE TRIGGER update_total_damage_on_insert
AFTER INSERT ON PARTICIPATED
FOR EACH ROW
DECLARE
    new_total_damage INT;
BEGIN
    -- Calculate the new total damage for the accident
    SELECT SUM(damage_amount)
    INTO new_total_damage
    FROM PARTICIPATED
    WHERE report_number = :NEW.report_number;

    -- Update the total_damage in the ACCIDENT table
    UPDATE ACCIDENT
    SET total_damage = new_total_damage
    WHERE report_number = :NEW.report_number;
END;
/
