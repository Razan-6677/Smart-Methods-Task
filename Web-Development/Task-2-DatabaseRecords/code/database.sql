CREATE TABLE IF NOT EXISTS records (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INT NOT NULL,
    status TINYINT(1) NOT NULL DEFAULT 0
);

INSERT INTO records (name, age, status) VALUES
('Khaled', 25, 0),
('Razan', 22, 1),
('Raghad', 28, 0);
