SELECT c.regno, c.model, COUNT(DISTINCT p.report_number) AS accident_count, SUM(p.damage_amount) AS total_damage
FROM CAR c
JOIN PARTICIPATED p ON c.regno = p.regno
JOIN ACCIDENT a ON p.report_number = a.report_number
GROUP BY c.regno, c.model
HAVING COUNT(DISTINCT p.report_number) > 1;  -- Cars involved in more than one accident
