<html>
<head>
  <meta charset="utf-8">
  <link rel="stylesheet" type="text/css" href="otenkikun.css">
  <title>NAMAEHAMADANAI</title>
  <link rel="shortcut icon" href="icon.ico">
  <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
</head>
<body class='section1'>
  <div class="title">SETUP</br></div>
        <label class="control-label"></label>
          <!--<div class="select-wrap select-primary">-->
  <form action="form.php" method="post">
    <?php
    while(date('s')%2==0){
      sleep(1);
    }
    $url = "info.json";
    $json = file_get_contents($url);
    $arr = json_decode($json,TRUE);
    echo'<div class="time_title">ON TIME</div>';
    echo '<div class="time_label">';
    echo'<div class="select-wrap select-primary" >';
    echo '<select  class="time" id="hour" name="hour" >';
    for($i=0;$i<=23;$i++){
      if($i==$arr['hour']){
        echo '<option value="'.$i.'"selected>'.$i.'h</option>';
      }
      else{
        echo '<option value="'.$i.'">'.$i.'h</option>';
      }
    }
    echo '</select>';
    echo '<select class="time" id="minute" name="minute">';
    for($i=0;$i<=11;$i++){
      if(($i*5)==$arr['minute']){
        echo '<option value="'.($i*5).'"selected>'.($i*5).'m</option>';
      }
      else{
      echo '<option value="'.($i*5).'">'.($i*5).'m</option>';
      }
    }
    echo '</select>';
    echo '</br>';
    echo '</div>';
    echo '</div>';
    echo'<div class="place_title">PLACE</div>';
    echo'<div class="select-wrap select-primary">';
    echo '<select id="place" name="place">';
    // ◯◯◯.csvに先程保存したCSVファイル名を入力します。
      $filename = 'place.csv';

      // fopenでファイルを開きます。
      $fp = fopen($filename, 'r');
      $i=0;
          // CSVファイルの行数の数だけ実行
          while($data = fgetcsv($fp)){

              // csvファイルの列数だけ実行
              if($data[1]==$arr['place']){
                echo '<option value="'.$data[1].'"selected>'.$data[0].'</option>';
              }
              else{
              echo '<option value="'.$data[1].'">'.$data[0].'</option>';
              }
              $i++;
          }
      // fcloseでファイルを閉じます。
      fclose($fp);
      echo'</select>';
      echo '</br>';
      echo '</div>';
     ?>
     <label class="label-checkbox">
       <input type="checkbox"  id='light' name='light' value='1'/>
       <span class="lever">LIGHT</span>
     </label>
    <input class='send' type="submit"　 value="SEND">
  </form>
</body>
</html>
