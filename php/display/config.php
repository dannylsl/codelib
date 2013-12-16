<?php
$mysql_server_name='localhost';
$mysql_username='root';
$mysql_password='123456';
$mysql_database='socwatch';
$conn=mysql_connect($mysql_server_name,
        $mysql_username,$mysql_password,
        $mysql_database);

if($conn){
    echo "DB CONNECTED<br>";
}else{
    echo "DB CONNECT FAILED<br>";
}
mysql_select_db($mysql_database,$conn);
//mysql_close($conn);
?>

