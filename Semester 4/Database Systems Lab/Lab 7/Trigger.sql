DELIMITER $$

CREATE TRIGGER display_driver_info_after_accident
AFTER INSERT ON accidents
FOR EACH ROW
BEGIN
    DECLARE driver_info VARCHAR(255);

    -- Retrieve driver information
    SELECT CONCAT('Driver Name: ', d.name, ', License: ', d.license_number, ', Phone: ', d.phone_number)
    INTO driver_info
    FROM drivers d
    WHERE d.driver_id = NEW.driver_id;

    -- Display the driver information (for debugging or logging purposes, you could use SELECT, or log it elsewhere)
    -- In real production, you could send the info to a log or external system.
    SELECT driver_info AS DriverDetails;

END $$

DELIMITER ;
