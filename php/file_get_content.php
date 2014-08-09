<?php
$smsText = urlencode("您的订单2014072082980已于07月20日16时发货 [ECSHOP]");
echo file_get_contents("http://utf8.sms.webchinese.cn/?Uid=dannylsl&Key=49ce16dfe3a3eebae928&smsMob=13910872954&smsText={$smsText}");
?>
