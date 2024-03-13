<?php
  include 'dbconn.php';
  $name = $_POST['name'];
  $city = $_POST['city'];
  $age = $_POST['age'];
  $age = (int)$age;

  $sql = "INSERT INTO klienti (name, city, age) VALUES ('$name', '$city', $age);";
  $result = $conn->query($sql);
?>
