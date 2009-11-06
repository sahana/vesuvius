#!/usr/bin/perl 

my $flag=0;
while(<>)
{
    chomp;
    if ($_ =~ /^--- (.*?)$/){
        if ($flag==0){
            print "\t//$1\n";
            print "\techo sprintf(\$section_seperator,_(\"$1\"));\n\n\t\$body = array (\n";
            $flag=1;
        }else{
            print "\t\t\t\t);\nshn_show_form(\$body);\n\n";
            print "\t//$1\n";
            print "\techo sprintf(\$section_seperator,_(\"$1\"));\n\n\t\$body = array (\n";
        }
    }else{
        ($caption,$name,$type,$list) = split /\|/;
        print "\t\t\t\tarray ('type' => '$type', 'desc' => _('$caption'), 'name' => '$name' ,'br' => 1 ";
        if($list){
            print ", 'options' => array ( \n";
            @vals = split (/;/,$list);
            $output = undef;
            foreach $val (@vals){
                ($desc,$value) = split (/,/,$val);
                $output .= "\t\t\t\t\tarray('drop_desc' => _('$desc'), 'value' => '$value'),\n";
            }
            $output =~ s/,$//;
            print $output."\t\t\t\t\t)\n";
        }
        print "),\n";
    }
}

print "\t\t\t\t));\nshn_show_form(\$body);\n\n";
