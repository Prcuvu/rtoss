<?php
require("./fav_settings.php");
require("./fav_strings.php");

$db = new PDO('sqlite:./'.$sqlite_file, '', '', array(PDO::ATTR_PERSISTENT => true));

$iPass=val($_POST,"pwd");
$iAction=val($_GET,'action');

echo '<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>'.$MyFav_Action_Title.'</title>
<link href="./style.css" rel="stylesheet" type="text/css">';
if ($InSidebar) {	echo '<STYLE type="text/css"><!--
body {font-size: 9pt;}
--></STYLE>';
}
echo '</head>';

require("./fav_header.htm");

if (!isset($_SESSION['isLogined']) && !viewAuth()) {
	if (($iAction=="go") && ($iPass) && isset($_POST["h_id"]) && (($iPass==$FavPasswd) || ($iPass==$ViewPassword))) {
		viewAuth('login',$iPass);
    	$qry="SELECT * FROM Fav WHERE id = ".intval($_POST["h_id"]);
		$rs=$db->query($qry);
		$row = $rs->fetch(PDO::FETCH_ASSOC);
		header("Location: ".$row["addr"]);
	} else {
		if (($iAction=="go") && (!$iPass)) {
			echo $MyFav_PasswdPrompt.'<form action="'.$_SERVER['PHP_SELF'].'?action=go" method="post">
	<input type="hidden" name="h_id" value="'.intval($_GET["id"]).'">
    <input type="password" name="pwd">
    <input type="submit" name="Submit" value="登入">
    '.$MyFav_BackHTML.'
</form>';
		} else {
			if(!isset($_POST['pwd'])) {
				echo $MyFav_PasswdPrompt.'<form action="'.$_SERVER['PHP_SELF'].'?'.$_SERVER['QUERY_STRING'].'" method="post">
	    <input type="password" name="pwd">
	    <input type="submit" name="Submit" value="登入">
	    '.$MyFav_BackHTML.'
	</form>';
			} else
				if(!logInOut(val($_POST,'pwd')))
					echo $MyFav_AccessDeny.'<br><center>'.$MyFav_BackHTML.'</center>';
		}
	}
}
if (isset($_SESSION['isLogined']) || viewAuth()) {
   switch ($iAction) {
    case "add":
      $_GET['url']=preg_replace('/%([0189a-fA-F])/','%25\1',urlencode($_GET['url'])); // encodes url again, preserve %00-%1F,%80-%FF
      $_GET['name']=urlencode(jsUCEsc2utf8($_GET['name'])); // encodes name again
      header("Location: ".$BaseURL."fav_add.php?".toQueryString("catid",'name','url').$SidebarSuffix2);
      break;
    case "edit":
      header("Location: ".$BaseURL."fav_edit.php?".toQueryString('id').$SidebarSuffix2);
      break;
    case "delete":
      header("Location: ".$BaseURL."fav_del.php?".toQueryString('id').$SidebarSuffix2);
      break;
    case "order":
      header("Location: ".$BaseURL."fav_reorder_2.php?".toQueryString('id').$SidebarSuffix2);
      break;
    case "go":
      $qry="SELECT * FROM Fav WHERE id = ".$_GET["id"];
	  $rs=$db->query($qry);
	  $row = $rs->fetch(PDO::FETCH_ASSOC);
      header("Location: ".$row["addr"]);
      break;
    case "opt":
      $qry="VACUUM Fav";
	  $rs=$db->exec($qry);
      echo $MyFav_Action_Optimized.'<br><center>'.$MyFav_BackHTML.'</center>';
      break;
    default:
      echo $MyFav_Action_UnknowOpCode.'<br><center>'.$MyFav_BackHTML.'</center>';
      break;
  }
}
require("./fav_footer.htm"); ?>
</body>
</html>

