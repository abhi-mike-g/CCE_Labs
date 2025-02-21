SET serveroutput ON

DECLARE
    -- Declare a cursor to hold the result set
    CURSOR cars_cursor IS
        SELECT c.regno, c.model, COUNT(DISTINCT p.report_number) AS accident_count, SUM(p.damage_amount) AS total_damage
        FROM CAR c
        JOIN PARTICIPATED p ON c.regno = p.regno
        JOIN ACCIDENT a ON p.report_number = a.report_number
        GROUP BY c.regno, c.model
        HAVING COUNT(DISTINCT p.report_number) > 1;  -- Cars involved in more than one accident

    -- Declare variables to store the results from the cursor
    v_regno CAR.regno%TYPE;
    v_model CAR.model%TYPE;
    v_accident_count NUMBER;
    v_total_damage NUMBER;
BEGIN
    -- Open the cursor and loop through the results
    FOR car_record IN cars_cursor LOOP
        -- Fetch the data from the cursor and assign it to the variables
        v_regno := car_record.regno;
        v_model := car_record.model;
        v_accident_count := car_record.accident_count;
        v_total_damage := car_record.total_damage;

        -- Output the results (using DBMS_OUTPUT for display)
        DBMS_OUTPUT.PUT_LINE('Car Registration Number: ' || v_regno);
        DBMS_OUTPUT.PUT_LINE('Car Model: ' || v_model);
        DBMS_OUTPUT.PUT_LINE('Accident Count: ' || v_accident_count);
        DBMS_OUTPUT.PUT_LINE('Total Damage: ' || v_total_damage);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    END LOOP;
END;
/
