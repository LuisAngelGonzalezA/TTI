<?php

include("conexion.php");

	$sql = "SELECT * FROM sensadoB  ORDER BY id_sensado_b DESC 
	LIMIT 1";
	$json = array();
	$resultado = mysqli_query($conn,$sql);

	$operacion["operacion"] = '6';
	$json['datos'][] = $operacion;
	if($sql){
		
		while($reg=$resultado->fetch_assoc()){
			$json['datos'][] = $reg;
		}
		mysqli_close($conn);
		echo json_encode($json);
	}

?>
