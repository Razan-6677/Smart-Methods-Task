<?php
if(isset($_GET['state'])) {
    $state = $_GET['state'];
    file_put_contents("t.txt", $state);
    echo "Command sent: " . $state;
}
?>