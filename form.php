<html>
<head><title>form.php</title>
<link rel="stylesheet" type="text/css" href="form.css"></head>
<body>
<?php

  $place = $_POST['place'];
  $hour =$_POST['hour'];
  $minute =$_POST['minute'];
  $light=$_POST['light'];

  $value_arry=[
  'place'=>$place,
  'hour'=>(int)$hour,
  'minute'=>(int)$minute,
  'light'=>(int)$light,
  'now'=>(int)date('m')*60+(int)date('s')
  ];

  while(date('s')%2==0){
    sleep(1);
  }

  $jsonstr=json_encode($value_arry,JSON_UNESCAPED_UNICODE | JSON_PRETTY_PRINT);
  file_put_contents("info.json",$jsonstr);
  //print($place);

?>
<meta http-equiv ='Refresh' content='0;url=otenkikun.php'>
</body>
</html>
