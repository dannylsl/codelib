<?php
class SocData{
    var $cstate = array();
    var $pstate = array();
    var $ncstate = array();
    var $wakeups;
    var $corenum;

    function __construct(array()){
        echo "__construct called\n";
    }

    function __destruct(){
        echo "__destruct called\n";
    }
};

?>
