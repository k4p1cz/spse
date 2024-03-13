<?php
  include 'dbconn.php';
  $sql = "SELECT * FROM klienti";
  $result = $conn->query($sql);
  $return = array();
   if ($result->num_rows > 0) {
       while ($row = $result->fetch_assoc()) {
        $return[] = $row;
       }
   }

   echo json_encode($return);
   $conn->close();
?>
