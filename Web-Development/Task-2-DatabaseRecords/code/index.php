<?php
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

$host = "sql101.infinityfree.com";
$user = "if0_42398956";
$pass = "MuvUb0uivRZsh";
$db   = "if0_42398956_teskdb";

try {
    $conn = new mysqli($host, $user, $pass, $db);
} catch (mysqli_sql_exception $e) {
    if (isset($_POST['action']) && ($_POST['action'] === 'toggle' || $_POST['action'] === 'delete')) {
        header('Content-Type: application/json');
        echo json_encode(["success" => false, "error" => "DB connection failed: " . $e->getMessage()]);
        exit;
    }
    die("Connection failed: " . $e->getMessage());
}

if (isset($_POST['action']) && $_POST['action'] === 'toggle') {
    header('Content-Type: application/json');

    try {
        $id = intval($_POST['id']);

        $stmt = $conn->prepare("UPDATE records SET status = 1 - status WHERE id = ?");
        $stmt->bind_param("i", $id);
        $stmt->execute();
        $stmt->close();

        $stmt2 = $conn->prepare("SELECT status FROM records WHERE id = ?");
        $stmt2->bind_param("i", $id);
        $stmt2->execute();
        $result = $stmt2->get_result();
        $row = $result->fetch_assoc();
        $stmt2->close();

        if ($row) {
            echo json_encode(["success" => true, "status" => (int)$row['status']]);
        } else {
            echo json_encode(["success" => false, "error" => "Record not found"]);
        }
    } catch (mysqli_sql_exception $e) {
        echo json_encode(["success" => false, "error" => $e->getMessage()]);
    }
    exit;
}

if (isset($_POST['action']) && $_POST['action'] === 'delete') {
    header('Content-Type: application/json');

    try {
        $id = intval($_POST['id']);

        $stmt = $conn->prepare("DELETE FROM records WHERE id = ?");
        $stmt->bind_param("i", $id);
        $stmt->execute();
        $deleted = $stmt->affected_rows > 0;
        $stmt->close();

        echo json_encode(["success" => $deleted]);
    } catch (mysqli_sql_exception $e) {
        echo json_encode(["success" => false, "error" => $e->getMessage()]);
    }
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['name'], $_POST['age'])) {
    $name = trim($_POST['name']);
    $age  = intval($_POST['age']);

    if ($name !== '' && $age > 0) {
        $stmt = $conn->prepare("INSERT INTO records (name, age, status) VALUES (?, ?, 0)");
        $stmt->bind_param("si", $name, $age);
        $stmt->execute();
        $stmt->close();
    }

    header("Location: index.php");
    exit;
}

$records = $conn->query("SELECT * FROM records ORDER BY id ASC");
?>
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Records Manager</title>
<link rel="stylesheet" href="style.css">
</head>
<body>

<div class="container">
    <h1>Records Manager</h1>

    <form class="record-form" method="POST" action="index.php">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" required>

        <label for="age">Age</label>
        <input type="number" id="age" name="age" min="1" required>

        <button type="submit">Submit</button>
    </form>

    <table class="records-table">
        <thead>
            <tr>
                <th>ID</th>
                <th>Name</th>
                <th>Age</th>
                <th>Status</th>
                <th>Action</th>
            </tr>
        </thead>
        <tbody id="records-body">
            <?php $rowNumber = 1; while ($row = $records->fetch_assoc()): ?>
            <tr data-row-id="<?= $row['id'] ?>">
                <td><?= $rowNumber++ ?></td>
                <td><?= htmlspecialchars($row['name']) ?></td>
                <td><?= $row['age'] ?></td>
                <td class="status-cell"><?= $row['status'] ?></td>
                <td class="action-cell">
                    <button class="toggle-btn" data-id="<?= $row['id'] ?>">Toggle</button>
                    <button class="delete-btn" data-id="<?= $row['id'] ?>">Delete</button>
                </td>
            </tr>
            <?php endwhile; ?>
        </tbody>
    </table>
</div>

<script src="script.js"></script>
</body>
</html>
<?php $conn->close(); ?>
