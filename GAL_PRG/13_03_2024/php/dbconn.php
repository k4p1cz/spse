<?php
    $servername = "127.0.0.1";
    $username = "root";
    $password = "";
    $dbname = "kapitanov";

    $conn = new mysqli($servername, $username, $password, $dbname);
    $conn->set_charset("utf8mb4");

    if ($conn->connect_error) {
        die("Připojení k databázi selhalo: " . $conn->connect_error);
    }
?>
