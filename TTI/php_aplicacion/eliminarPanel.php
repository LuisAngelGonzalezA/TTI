<?php

include("conexion.php");

$id=$_GET["id_panel"];
$isEliminado="1";
$json = array();

$sql = "UPDATE panel_solar SET isEliminado='{$isEliminado}' WHERE id_panel='{$id}'";

	$operacion["operacion"] = '3';
	$json['datos'][] = $operacion;
	
	if (mysqli_query($conn,$sql) === TRUE) {
		$json['datos'][] = $result;
	    echo json_encode($json);
	} else {
		echo json_encode($json);
	}	

mysqli_close($conn);

?>
