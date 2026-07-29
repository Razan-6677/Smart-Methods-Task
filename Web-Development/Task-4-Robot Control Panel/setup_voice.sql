-- شغّلي هذا الكود مرة واحدة بتبويب SQL في phpMyAdmin (بعد كود setup.sql)

CREATE TABLE voice_notes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    text_content VARCHAR(500) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
