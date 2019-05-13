<?php

include("conexion.php");

$id=$_GET["id_panel"];

	$sql = "SELECT * FROM panel_solar WHERE id_panel='{$id}'";
	$json = array();
	$resultado = mysqli_query($conn,$sql);

	if($sql){

		$operacion["operacion"] = '1';
		$json['datos'][] = $operacion;
		
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		

		mysqli_close($conn);
		echo json_encode($json);
	}

?>
