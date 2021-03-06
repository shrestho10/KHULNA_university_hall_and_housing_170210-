<?php
include_once UTILITY.'class.util.inc';
include_once MODULES_HOUSING_BAO.'class.housingRoomAssignbao.inc';



$_HousingRoomAssignBAO = new HousingRoomAssignBAO();
$_DB = DBUtil::getInstance();

/* saving a new Housing Room Assign account*/
if(isset($_POST['save']))
{
	
	$HousingRoomAssign = new HousingRoomAssign();
	$HousingRoomAssign->setHouseId($_GET['h_id']);	
    $HousingRoomAssign->setRoomId($_GET['r_id']);
    $HousingRoomAssign->setAppointDate($_DB->secureinput(date("Y/m/d")));
    if(isset($_POST['student_add'])){

    	$Result = $_HousingRoomAssignBAO->getUserFromUniversityID($_POST['student_add']);
    	if($Result->getIsSuccess())
    	{
    		$User = $Result->getResultObject();
    		$id = $User->getID();
    		$HousingRoomAssign->setUserId($id);
    	} 
	}
     
	$_HousingRoomAssignBAO->createHousingRoomAssign($HousingRoomAssign);		 
}


/* deleting an existing Housing Room Assign */
if(isset($_GET['del']) && isset($_GET['h_id']))
{
	$HousingRoomAssign = new HousingRoomAssign();	
	$HousingRoomAssign->setUserid($_GET["del"]);	
	$HousingRoomAssign->setRoomid($_GET['h_id']);
	$HousingRoomAssign->setHouseid($_GET['r_id']);

	$HousingRoomAssign->setCurrentDate($_DB->secureinput(date("Y/m/d")));

	$_HousingRoomAssignBAO->deleteHousingRoomAssign($HousingRoomAssign); //reading the Housing object from the result object

	header("Location:".PageUtil::$HOUSING_ROOM_ASSIGN."?h_id=".$_GET['h_id']. "&r_id=".$_GET['r_id']);
}





if(isset($_GET['view']))
{
	$HousingRoomAssign = new HousingRoomAssign();	
	$HousingRoomAssign->setHouseId($_GET['view']);	
	$getROW = $_HousingRoomAssignBAO->readHousingRoomAssign($HousingRoomAssign)->getResultObject(); //reading the Housing Room Assign object from the result object

}

