document.addEventListener("DOMContentLoaded", function () {
    const tableBody = document.getElementById("records-body");

    tableBody.addEventListener("click", function (e) {
        if (e.target.classList.contains("toggle-btn")) {
            handleToggle(e.target);
        } else if (e.target.classList.contains("delete-btn")) {
            handleDelete(e.target);
        }
    });

    function handleToggle(btn) {
        const id = btn.getAttribute("data-id");
        const row = btn.closest("tr");
        const statusCell = row.querySelector(".status-cell");

        btn.disabled = true;

        const formData = new FormData();
        formData.append("action", "toggle");
        formData.append("id", id);

        fetch("index.php", {
            method: "POST",
            body: formData
        })
            .then(function (response) {
                return response.text().then(function (text) {
                    try {
                        return JSON.parse(text);
                    } catch (e) {
                        throw new Error("Invalid server response: " + text);
                    }
                });
            })
            .then(function (data) {
                if (data.success) {
                    statusCell.textContent = data.status;
                } else {
                    alert("Failed to update status: " + (data.error || "unknown error"));
                }
            })
            .catch(function (error) {
                console.error("Error:", error);
                alert("Server connection failed. Check console for details.");
            })
            .finally(function () {
                btn.disabled = false;
            });
    }

    function renumberRows() {
        const rows = tableBody.querySelectorAll("tr");
        rows.forEach(function (row, index) {
            row.querySelector("td:first-child").textContent = index + 1;
        });
    }

    function handleDelete(btn) {
        const id = btn.getAttribute("data-id");
        const row = btn.closest("tr");

        if (!confirm("Delete this record?")) {
            return;
        }

        btn.disabled = true;

        const formData = new FormData();
        formData.append("action", "delete");
        formData.append("id", id);

        fetch("index.php", {
            method: "POST",
            body: formData
        })
            .then(function (response) {
                return response.text().then(function (text) {
                    try {
                        return JSON.parse(text);
                    } catch (e) {
                        throw new Error("Invalid server response: " + text);
                    }
                });
            })
            .then(function (data) {
                if (data.success) {
                    row.remove();
                    renumberRows();
                } else {
                    alert("Failed to delete record: " + (data.error || "unknown error"));
                    btn.disabled = false;
                }
            })
            .catch(function (error) {
                console.error("Error:", error);
                alert("Server connection failed. Check console for details.");
                btn.disabled = false;
            });
    }
});
