SET serveroutput ON

DECLARE
    -- Declare a cursor to hold the result set
    CURSOR drivers_cursor IS
        SELECT DISTINCT p.driver_id, p.regno
        FROM PARTICIPATED p
        LEFT JOIN OWNS o ON p.driver_id = o.driver_id AND p.regno = o.regno
        WHERE o.driver_id IS NULL;  -- Driver does not own the car involved in the accident

    -- Declare variables to store the results from the cursor
    v_driver_id PARTICIPATED.driver_id%TYPE;
    v_regno PARTICIPATED.regno%TYPE;
BEGIN
    -- Open the cursor and loop through the results
    FOR driver_record IN drivers_cursor LOOP
        -- Fetch the data from the cursor and assign it to the variables
        v_driver_id := driver_record.driver_id;
        v_regno := driver_record.regno;

        -- Output the results (using DBMS_OUTPUT for display)
        DBMS_OUTPUT.PUT_LINE('Driver ID: ' || v_driver_id || ' | Car Registration Number: ' || v_regno);
    END LOOP;
END;
/
