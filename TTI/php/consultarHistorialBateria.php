<?php

include("conexion.php");

	$sql = "SELECT * FROM bateria";
	$json = array();
	$resultado = mysqli_query($conn,$sql);

	$operacion["operacion"] = '4';
	$json['datos'][] = $operacion;
	if($sql){
		
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		mysqli_close($conn);
		echo json_encode($json);
	}

?>
