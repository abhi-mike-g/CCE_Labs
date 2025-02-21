SET serveroutput ON

DECLARE
    -- Declare a cursor to hold the result set
    CURSOR locations_cursor IS
        SELECT a.location, AVG(p.damage_amount) AS avg_damage
        FROM ACCIDENT a
        JOIN PARTICIPATED p ON a.report_number = p.report_number
        GROUP BY a.location;

    -- Declare variables to store the results from the cursor
    v_location ACCIDENT.location%TYPE;
    v_avg_damage NUMBER;
BEGIN
    -- Open the cursor and loop through the results
    FOR location_record IN locations_cursor LOOP
        -- Fetch the data from the cursor and assign it to the variables
        v_location := location_record.location;
        v_avg_damage := location_record.avg_damage;

        -- Output the results (using DBMS_OUTPUT for display)
        DBMS_OUTPUT.PUT_LINE('Location: ' || v_location);
        DBMS_OUTPUT.PUT_LINE('Average Damage: ' || v_avg_damage);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    END LOOP;
END;
/
