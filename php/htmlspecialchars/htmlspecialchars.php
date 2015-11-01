<?php
$str = "Hello World <br> <p>&gt; aaa</p><p>&gt;Narutom</p> ";
echo htmlspecialchars_decode($str);
echo "\n==================<br>\n";
echo htmlspecialchars($str);
echo "\n==================<br>\n";
echo htmlspecialchars_decode($str);
?>
