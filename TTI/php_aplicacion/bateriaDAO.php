<?php

include("conexion.php");

	$sql = "SELECT b.*, h.activo FROM bateria b
	left join  historial_bateria_panel h on b.id_bateria = h.id_bateria
	where b.isEliminado=0 GROUP BY b.nombre";
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
