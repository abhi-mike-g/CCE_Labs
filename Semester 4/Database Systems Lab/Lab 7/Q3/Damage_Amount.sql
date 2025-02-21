SET serveroutput ON

DECLARE
    -- Declare a cursor to hold the result set
    CURSOR cars_cursor IS
        SELECT c.regno, c.model, SUM(p.damage_amount) AS total_damage
        FROM CAR c
        JOIN PARTICIPATED p ON c.regno = p.regno
        JOIN ACCIDENT a ON p.report_number = a.report_number
        GROUP BY c.regno, c.model
        HAVING SUM(p.damage_amount) > 50000;  -- Total damage exceeds $50,000

    -- Declare variables to store the results from the cursor
    v_regno CAR.regno%TYPE;
    v_model CAR.model%TYPE;
    v_total_damage NUMBER;
BEGIN
    -- Open the cursor and loop through the results
    FOR car_record IN cars_cursor LOOP
        -- Fetch the data from the cursor and assign it to the variables
        v_regno := car_record.regno;
        v_model := car_record.model;
        v_total_damage := car_record.total_damage;

        -- Output the results (using DBMS_OUTPUT for display)
        DBMS_OUTPUT.PUT_LINE('Car Registration Number: ' || v_regno);
        DBMS_OUTPUT.PUT_LINE('Car Model: ' || v_model);
        DBMS_OUTPUT.PUT_LINE('Total Damage: ' || v_total_damage);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    END LOOP;
END;
/
