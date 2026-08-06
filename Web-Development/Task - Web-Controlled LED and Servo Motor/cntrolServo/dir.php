<?php
if(isset($_POST['command'])) {
    $cmd = $_POST['command'];
    file_put_contents("dir.txt", $cmd);
    echo json_encode(["status" => "success", "button" => $cmd, "stored_as" => $cmd]);
}
?>