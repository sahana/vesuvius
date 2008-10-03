<?php
#####################################################################################
#
# To Print Current Week start date and End Date you can use this class
# class_week_start_end_date.php
# ver 1
# 26-Sep-05
# By G. Sabari Nathan.
# email : haisabari@hotmail.com
# india

# for example you want to see the current week start date and end date use this class 

# Result : 09/25-30/05 ---> (date/week start date - end date, year



#####################################################################################
class weekstartend
{
    
    /** calculate users local time offset  */
    
    function setOffset()
    {
        $this->cal_offset =  (time() + (($this->user_offset) * 3600));
    }
    
    /** find # of days in month */
    
    function setCheckcell()
    {
        $this->check_cell = date('t', $this->cal_offset);
    }
    
    /** find which day the 1st falls on and calculate # of empty cells at beginning of month */
    
    function setCol()
    {	
	    if($this->cal_type == 0)
        {
        	$this->col = date('w', mktime(0,0,0,date('n', $this->cal_offset),1,date('y', $this->cal_offset)));
        }
        elseif($this->cal_type == 1)
        {
        	if(date('w', mktime(0,0,0,date('n', $this->cal_offset),1,date('y', $this->cal_offset))) == 0)
        	{
	        	/** prevent colspan from being a neg integer */
	        	
        		$this->col = 0;
        	}
        	else
        	{
	        	$this->col = date('w', mktime(0,0,0,date('n', $this->cal_offset),1,date('y', $this->cal_offset))) - 1;
        	}
        		
        }
    }
    
    /** numeric representation of current month */
    
    function setGetmonth()
    {
        $this->get_month = date('n', $this->cal_offset);
    }

    #############################################################
    # Generate week days function
    #############################################################
    
    function gen_cal()
    {
	    $this->setOffset();
        $this->setCheckcell();
        $this->setCol();
		
		if($this->cal_type == 0)
        {
        	$week = array($this->sun,$this->mon,$this->tue,$this->wed,$this->thu,$this->fri,$this->sat);
        }
        elseif($this->cal_type == 1)
        {
       		$week = array($this->mon,$this->tue,$this->wed,$this->thu,$this->fri,$this->sat,$this->sun);
        }
        else
        {
	        $week = array($this->sun,$this->mon,$this->tue,$this->wed,$this->thu,$this->fri,$this->sat);
        }
        /** generate calendar table */
        
		$a = 8 - $this->col;
        $b = 15 - $this->col;
        $c = 22 - $this->col;
        $d = 29 - $this->col;
        $e = 36 - $this->col;
  
		 $mday = date("m");
  		 $year = date("y");	

		if((date('j', $this->cal_offset) < $a ))
		{
			 $vEndDate = $a-1;
			 $rval = /*"1-".*/$vEndDate;
			 echo $mday."/".$rval."/".$year;
		}
	   if( (date('j', $this->cal_offset) >= $a) &&  (date('j', $this->cal_offset) < $b ) )
		   {
			  $vEndDate = $b-1;
			  $rval = /*$a."-".*/$vEndDate;
			  echo $mday."/".$rval."/".$year;
			}
		if( (date('j', $this->cal_offset)>= $b ) && (date('j', $this->cal_offset) < $c ) )
			{
			  $vEndDate = $c-1;
			  $rval = /*$b."-".*/$vEndDate;
			  echo $mday."/".$rval."/".$year;
			}
		if( (date('j', $this->cal_offset) > $c) && (date('j', $this->cal_offset) < $d) )
			{
                          $vEndDate = $d-1;
			  $rval = /*$c."-".*/$vEndDate;
			  echo $mday."/".$rval."/".$year;
			}
		if(date('j', $this->cal_offset) >= $d)
		{
			  /*$rval =  $d."-".*/ ($this->check_cell);
			  echo $mday."/".$rval."/".$year;
		}
    }

}
?>