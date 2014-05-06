<?php
/*
date_default_timezone_set('Asia/Shanghai');
for($i =1; $i < 3; $i++) {
$week=$i;
echo "\nWeek $i   \n";
echo "Year:".date('Y', time());
echo " Year timestamp:".mktime(0, 0, 0, 1, 1, date('Y', time()));
echo " Day TimeStamp:".mktime(0, 0, 0, 1, 2, 1970)."\n";
echo date('Y-m-d', mktime(0, 0, 0, 1, 1, date('Y', time())) + (($week -1) * 7 * 86400));
echo "\n";
}
echo "\n\n\n";
*/
function get_week_startday($year, $weekno) {
    $year_start_date = $year.'-01-01';
//    echo $year_start_date;
//    echo "year_start_date_w:".date('w',strtotime($year_start_date));
    $year_start_date_w = date('w',strtotime($year_start_date)); //day number in a week

    if($weekno == 0) {
        return 0;
    }else if($weekno == 1) {
        $week['start'] = $year_start_date;
        if($year_start_date_w == 0){
            $week['end'] = $year_start_date;
        }else {
            $week['end'] = $year.'-01-'.(8-$year_start_date_w);
        }
    }else {
        if($year_start_date_w == 0){
            $ww1_end = $year_start_date;
        }else {
            $ww1_end = $year.'-01-'.(8-$year_start_date_w);
        }
        $ww2_start = date('Y-m-d',strtotime('+1 day',strtotime($ww1_end)));
        $week['start'] = date('Y-m-d',strtotime('+'.($weekno-2).' week',strtotime($ww2_start)));
        $week['end'] = date('Y-m-d',strtotime('+6 day',strtotime($week['start'])));
    }
    return $week;
}

$ret = get_week_startday(2014,17);

print_r($ret);
?>
