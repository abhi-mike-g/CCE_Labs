SELECT a.location, AVG(p.damage_amount) AS avg_damage
FROM ACCIDENT a
JOIN PARTICIPATED p ON a.report_number = p.report_number
GROUP BY a.location;
