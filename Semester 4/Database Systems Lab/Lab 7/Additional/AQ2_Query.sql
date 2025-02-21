SELECT DISTINCT p.driver_id, p.regno
FROM PARTICIPATED p
LEFT JOIN OWNS o ON p.driver_id = o.driver_id AND p.regno = o.regno
WHERE o.driver_id IS NULL;  -- Driver does not own the car involved in the accident
