<?php
// بيانات الاتصال بقاعدة البيانات - غيّرها ببياناتك من InfinityFree
$host = "sql312.infinityfree.com";      // اسم السيرفر (Hostname)
$user = "if0_42493898";                 // اسم المستخدم
$pass = "AvH8wnYsQoW";                  // كلمة المرور
$dbname = "if0_42493898_control_db";    // اسم قاعدة البيانات

$conn = new mysqli($host, $user, $pass, $dbname);

if ($conn->connect_error) {
    die(json_encode(["status" => "error", "message" => "فشل الاتصال: " . $conn->connect_error]));
}
?>
