<?php
$host = "sql312.infinityfree.com";     
$user = "if0_42493898";               
$pass = "AvH8wnYsQoW";                 
$dbname = "if0_42493898_control_db";    
$conn = new mysqli($host, $user, $pass, $dbname);

if ($conn->connect_error) {
    die(json_encode(["status" => "error", "message" => "فشل الاتصال: " . $conn->connect_error]));
}
?>
