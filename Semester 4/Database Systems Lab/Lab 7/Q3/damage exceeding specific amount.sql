SELECT c.regno, c.model, SUM(p.damage_amount) AS total_damage
FROM CAR c
JOIN PARTICIPATED p ON c.regno = p.regno
JOIN ACCIDENT a ON p.report_number = a.report_number
GROUP BY c.regno, c.model
HAVING SUM(p.damage_amount) > 50000;  -- Total damage exceeds $50,000
