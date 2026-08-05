<?php
header('Content-Type: application/json');
include "db.php";

$stmt = $conn->prepare("SELECT command, updated_at FROM robot_state WHERE id = 1");
$stmt->execute();
$stmt->bind_result($command, $updated_at);

if ($stmt->fetch()) {
    echo json_encode(["command" => $command, "updated_at" => $updated_at]);
} else {
    echo json_encode(["status" => "error", "message" => "لا يوجد صف بـ id = 1"]);
}

$stmt->close();
$conn->close();
?>
