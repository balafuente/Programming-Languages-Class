#Blake LaFuente
#COSC 341
#Assignment 7

sub quadratic
{  #User enters values for quadratic equation
  print "The Quadratic equation is ax^2 + bx + c\nEnter your value for 'a': ";
  my $a = <STDIN>;
  print "Enter your value for 'b': ";
  my $b = <STDIN>;
  print "Enter your value for 'c': ";
  my $c = <STDIN>;
  chomp($a);
  chomp($b);
  chomp($c);

  if($b*$b - 4*$a*$c >= 0)
  #check to see if values are valid
   {
     #calculates and prints both solutions
      my $solution1 = (-$b + sqrt($b*$b - 4*$a*$c));
      my $solution2 = (-$b - sqrt($b*$b - 4*$a*$c));
       print "\nSolution 1 is $solution1. Solution 2 is $solution2.\n";
   }
   else
   {
       print "There are no solutions with those inputs.";
       #message if there are no solutions
   }
}

sub prime
{
  print "Enter a number to test if it is prime: ";
  my $number = <STDIN>;  #user input
  my $isPrime = 0;  #boolean if value is prime. Set to True
  chomp($number);
  if ($number < 0)
  { #answers less than zero
      print "\nThe number $number is negative.\n";
      $isPrime = 1;
  }
 if ($number > 2  && $number % 2 == 0)
 {  #number is not prime if greater than 2 and even
     print "\nThe number $number is not prime.\n";
     $isPrime = 1;
 }
 for(my $i = 3; $i < $number / 2; $i += 2)
 {  #loop to check if number is divisible by other numbers
     if ($number % $i == 0)
     {
         print "\nThe number $number is not prime.\n";
         $isPrime = 1;
         last;
     }
 }
 if($isPrime == 0)
 { #answer is prime
 	print "\nThe number $number is prime.\n";
 }
}

sub pi
{
  print "Enter the number of terms of pi equation: ";
  my $number = <STDIN>;  #user input
  chomp($number);
  my $answer = 0.0;
  my $denominator =  1;
  for(my $x = 0; $x < $number; $x++)
  { #loops equation by number of terms inputted by user
      if ($x % 2 == 0)
      { #add fractions if even
          $answer = $answer + (1.0/$denominator);
      }
      else
      { #subtract fractions if odd
          $answer = $answer - (1.0/$denominator);
      }
      $denominator  = $denominator + 2.0;
  }
  $answer = $answer * 4.0;
  print "\nThe value of pi is $answer\n";
}

sub tax
{
print("Enter Income: ");
my $income = <STDIN>;  #integer input
chomp($income);
print("Is the tax payer:\n1.single\n2.married\n");
print("Enter 'single' or 'married': "); #marital status string
my $status = <STDIN>;
chomp($status);
print ("Is the tax payer a:\n1.in-state resident\n");
print("2.out-of-state resident\nEnter 'i' or 'o': ");
my $state = <STDIN>; #residency character
chomp($state);
my $tax;
if(($state eq "i" || $state eq "I"))  #if in-state
{
        if($status eq "single") #if in-state and single
        {
            if($income < 30000 && $income >= 0)
            { #if in-state, single, and lower income
                $tax = $income *0.2;
                print "The tax amount is $tax.";
            }
            elsif($income >= 30000)
            { #if in-state, single and upper income
                $tax = $income * 0.25;
                print "The tax amount is $tax.";
            }
            else
            { #error message
                print "At least one input was invalid.";
            }
        }
        elsif($status eq "married") #if in-state and married
        {
            if($income >=0 && $income < 50000)
            { #if in-state, married, and lower income
                $tax = $income * 0.1;
                print "The tax amount is $tax.";
            }
            elsif($income >= 50000)
            { #if instate, married, and upper income
                $tax = $income * 0.15;
                print "The tax amount is $tax.";
            }
            else
            { #error message
                print "At least one input was invalid.";
            }
        }
        else
        { #error message
            print "At least one input was invalid.";
        }
    }
    elsif($state eq "o" || $state eq "O") #if out-of-state
    {

        if($status eq "single") #if out of state and single
        {
            if($income < 30000)
            {  #if out-of-state, single, and lower income
                $tax = $income *0.17;
                print "The tax amount is $tax.";
            }
            elsif($income >= 30000)
            { #if out-of-state, single, and upper income
                $tax = $income * 0.22;
                print "The tax amount is $tax.";
            }
            else
            { #error message
                print "At least one input was invalid.";
            }
        }
        elsif($status eq "married")
        { #if out of state and married
            if($income >=0 && $income < 50000)
            { #if out-of-state, married, and lower incomce
                $tax = $income * 0.7;
                print "The tax amount is $tax.";
            }
            elsif($income >= 50000)
            { #if out-of-state, married, and upper incomce
                $tax = $income * 0.12;
                print "The tax amount is $tax.";
            }
            else
            { #error message
                print "At least one input was invalid.";
            }
        }
        else
        { #error message
            print "At least one input was invalid.";
        }
    }
    else
    { #error message
        print "At least one input was invalid.";
    }

}

sub idpassword
{
	print "Enter First Name: ";
	my $fname = <STDIN>; #user input first name
	print "Enter Last Name: ";
	my $lname = <STDIN>; #user input last name
	chomp($fname);
	chomp($lname);
	my $username = substr($fname, 0, 1).$lastname;
  #username = first letter of first name period last name
	my $password = substr($fname, 0, 1).substr($fname, length($fname)-1, 1).substr($lname,
					 0,3).length($lname);
  #password = first letter of first name, last letter of first name, first three letters
  #of last name, and length of last name
	$username = uc($username);
	$password = uc($password);
	print "The username is $username and the password is $password.";
}

sub score
{

	my $max = 0;
	my $min = 0;
	my $total = 0;
	my $size = 0;
	my $score;
	my $average;
  my $max_name;
  my $min_name;
  my @splitLine;
  printf("Enter student names and scores.\nPress 'q' or 'Q' to finish.\n");
  while(1)
  {
    my $line = <STDIN>;
		chomp($line);
    if(length($line) == 1 && $line eq "q" || $line eq "Q")
    { #ends loop when user inputs Q or q
      last;
    }
    else
    {
      @splitLine = split(/ /, $line); #splits line to get name and score
      $name = $splitLine[0];
      $score = $splitLine[1];
      if ($total == 0)
      {
        $max = $score; #first entry is max
        $max_name = $name;
      }
      if($score > $max)
      {
        $max = $score;  # new max if score is greater than current max
        $max_name = $name;
      }
      if($total == 0)
      {
        $min = $score;  #first entry is min
        $min_name = $name;
      }
      if ($score < $min)
      {
        $min = $score;  #new min if score is less than current min
        $min_name = $name;
      }
        $total += $score; #used to determine average
        $size++;
        }
    }
    $average = ($total/$size); #data outputted
    print "Average Score: $average\nMinimum Score: $min\nMaximum Score: $max\n";
    print "Student with minimum score:  $min_name\n";
    print "Student with maximum score: $max_name\n";
}


sub filesort
{ #get file names from user
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open(FIN, "<$infile"); #open files
	open(FOUT, ">$outfile");
	my @text = <FIN>; #create array of lines
	my $len = @text;
	my $temp;
#bubble sort of names
	for(my $i = 0; $i < $len - 1; $i++)
	{
    for(my $j = 0; $j < $len - 1 - $i; $j++)
    {
    if($text[$j] gt $text[$j + 1])
		{
			$temp = $text[$j];
			$text[$j] = $text[$j + 1];
			$text[$j + 1] = $temp;
		}
  }
  }
  for(my $lineNum = 0; $lineNum < $len; $lineNum++)
	{  #print array to output file
    chomp($text[$lineNum]);
    print FOUT "$text[$lineNum]\n";
	}
  close(FIN); #close files
  close(FOUT);
	print "Output file created.\n";
}

sub frequency
{	#get file names from user
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");		#open files
	open(FOUT, ">$outfile");
	my $lname;
	my $line;
	my %namecount;		#associative array
	my @splitLine;	
	my %entry;
	while($line = <FIN>)	#while line can be pulled from file
	{
		@splitLine = split(/\s+/,$line);
		$lname = $splitLine[0];			#grab just last name
		if(exists $namecount{$lname})
		{								#if name is in hash, add 1 to frequency
			$namecount{$lname} = $namecount{$lname} +1 ;	
		}
		else
		{			#if name is not in hash, add name with frequency of 1
			%entry = ($lname, 1);
      		my %oldnames = %namecount;
			%namecount = (%oldnames, %entry);
		}
	}

	foreach $lname (keys(%namecount))
	{					#for each last name, print name and total frequency
		print FOUT "Last Name: $lname Frequency: $namecount{$lname}\n";
	}
  close(FIN);			#close files
  close(FOUT);
	print "Output file created.\n";
}

sub power
{
	my $answer = $_[0];		#Parameters for equation answer^rounds
	my $rounds = $_[1];
	while ($rounds > 1)
	{ #non-recursive function
		$answer = $answer * $_[0];	#for each round, multiply answer by itself
		$rounds--;
	}
	return $answer;
}

sub factorial
{
	my $n = $_[0];		#parameter number to factorial

	if($n == 1)
	{				#base case
		return 1;
	}

	else
	{  #recursive if greater than one
		return $n * &factorial($n - 1);
	}

}

sub sort
{
	my @array = @_;			#parameter array from user
	my $len =  @array;		#length of array
	my $i;
	my $j;
	my $temp;
	my $min;
  #selection sort loops
	for($i = 0; $i <= $len - 1; $i++)
	{
		$min = $i;
		for($j = $i + 1; $j < $len; $j++)
		{
			if($array[$j] < $array[$min])
			{
				$min = $j;
			}
		}
		$temp = $array[$i];			#if integer is greater than the next one, switch them
		$array[$i] = $array[$min];
		$array[$min] = $temp;
	}
	return @array;
}

sub minmax
{
	my $len = @_;	#parameter array from user
	my $min = $_[0]; #set min and max to first number
	my $max = $_[0];
  my $val;

  for(my $i = 0; $i < $len - 2; $i++)
  { 						#traverse array
    $val = $_[$i];
    if($val > $max)
    {
      $max = $val; #new max if greater than current max
    }
    if($val < $min)
    {
      $min = $val; #new min if smaller than current min
    }
  }
  chomp($max);
  chomp($min);
	return($min, $max);
}


sub positives
{	#input file names from user
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");		#open files
	open(FOUT, ">$outfile");
	my $word;

	while($word = <FIN>)
	{
		chomp($word);
		if($word =~ /^[1-9][0-9]+$/)
		{ #print to file of non-zero number followed by more numbers
			print FOUT "$word\n";
		}
	}
  close(FIN);			#close files
  close(FOUT);
	print "Output file created.\n";
}

sub fractionals
{
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");
	open(FOUT, ">$outfile");
	my $word;

	while($word = <FIN>)
	{
		chomp($word);
		if($word =~ /^[0]\.[0-9]+$/)
		{#print to file if number starts with zero, then period,
    	 #then more numbers
			print FOUT "$word\n";
		}
	}
  close(FIN);
  close(FOUT);
	print "Output file created.\n";
}

sub emuid
{		#input file names from user
	print "What is the name of your input file?";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file?";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");
	open(FOUT, ">$outfile");   #open files

	my $word;

	while($word = <FIN>)
	{
		chomp($word); #only print to file if ID follows proper expression
		if($word =~ /^e00\d\d\d\d\d$/)
		{
			print FOUT "$word\n";
		}
	}
  close(FIN);
  close(FOUT);			#close files
	print "Output file created.\n";
}



sub emuweb
{	#get file names from user
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");		#open files
	open(FOUT, ">$outfile");

	my $word;

	while($word = <FIN>)
	{
		chomp($word);
		if($word =~ /^www.emich.edu(\/\D+)+.html$/)
		{ #only print to file if web address follows regular expression
			print FOUT "$word\n";
		}
	}
  close(FIN);		#close files
  close(FOUT);
	print "Output file created.\n";
}

sub whitespace
{	#input file names from user
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");		#open files
	open(FOUT, ">$outfile");

	my $line;

	while($line = <FIN>)
	{
		$line =~ s/\s+/ /g; #substitute ALL whitespace with single space
		print FOUT "$line\n";
	}
  close(FIN);		#close files
  close(FOUT);
}

sub areacode
{	#input file names from user
	print "What is the name of your input file? \n";
	my $infile = <STDIN>;
	chomp($infile);
	print "What is the name of your output file? \n";
	my $outfile = <STDIN>;
	chomp($outfile);
	open (FIN, "<$infile");	#open files
	open (FOUT, ">$outfile");


	while(my $line = <FIN>)
	{
		chomp($line);
		if($line =~ /^[\D]+ 715\d\d\d\d\d\d\d$/)
		{ #check regular expression for 715 area code
			$line =~ s/715/692/; #replace 715 with 692
		}
		print FOUT $line;
    print FOUT "\n";
	}
  close(FIN);	#close files
  close(FOUT);
}


sub main
{
	my $choice;
	while($choice != 19)
{   #print menu before every action
	print "\n          Menu\n______________________\n1.  Quadratic\n2.  Prime\n3.  Pi\n";
	print "4.  Tax\n5.  ID and Password\n6.  Score\n7.  File Sort\n8.  Frequency\n";
	print "9.  Power\n10. Factorial\n11. Sort\n12. Min and Max\n13. Positives\n";
	print "14. Fractionals\n15. EMUID\n16. EMUWEB\n17. White Space\n18. Area Code\n";
	print "19. Quit\n\nEnter Choice Number: ";

	$choice = <STDIN>;		#input menu choice from user
	if($choice == 1)
	{
		&quadratic();
	}

	if($choice == 2)
	{
		&prime();
	}

	if($choice == 3)
	{
		&pi();
	}

	if($choice == 4)
	{
		&tax();
	}

	if($choice == 5)
	{
		&idpassword();
	}

	if($choice == 6)
	{
		&score();
	}

	if($choice == 7)
	{
		&filesort();
	}

	if($choice == 8)
	{
		&frequency();
	}

	if($choice == 9)
	{	#input function parameters from user
		print "What number would you like to power: \n";
		my $input = <STDIN>;	
		chomp $input;
		print "What power would you like to compute for $input: \n";
		my $power = <STDIN>;
		chomp($power);
		my $ans = &power($input, $power); #answer is returned by power function
		print "$input to the $power power equals $ans";
	}

	if($choice == 10)
	{
		print "Enter number to factorial: ";
		my $input = <STDIN>;	#input parameter from user
		chomp($input);
		my $ans = &factorial($input);		#answer is returned by factorial function
		print "The factorial of $input is $ans.";

	}

	if($choice == 11)
	{
		print "Creating integer array.\nEnter integers on one line separated by";
		print " a single space:\n";
		my $line = <STDIN>;	#input entire array on one line
   		chomp($line);
		my @array = split(/ /, $line);	#create array out of inputted line
		@array = &sort(@array);	#sorted array is returned by sort function
		$len = @array;
		for (my $i = 0; $i < $len; $i++)	#print entire array
		{
			print "$array[$i] ";
		}
	}

	if($choice == 12)
	{
		print "Creating integer array.\nEnter integers on one line separated by";
		print " a single space:\n";
		my $line = <STDIN>;	#input entire array on one line
		my @array = split(/ /, $line); #creat array out of line
		my $min;
		my $max;
		my ($min, $max) = &minmax(@array, $min, $max); 
		#min and max are returned by minmax function
		print "The Minimum value is $min.\nThe Maximum value is $max.";
	}

	if($choice == 13)
	{
		&positives();
	}

	if($choice == 14)
	{
		&fractionals();
	}

	if($choice == 15)
	{
		&emuid();
	}

	if($choice == 16)
	{
		&emuweb();
	}

	if($choice == 17)
	{
		&whitespace();
	}

	if($choice == 18)
	{
		&areacode();
	}

	if($choice == 19)
	{
		print "Goodbye\n";
		last; #break loop
	}
}
}

&main();
