param ([string]$way="c:\test" ,[int]$num=32 )
Set-Location $way
[string]$test = $way+"\Less"
If(!(Test-Path $test) ) 
{New-Item -Path $way -Name "Less" -ItemType Directory}
Get-ChildItem | Foreach-Object {
 function Func ([string]$name=$_.BaseName)
 {
   [bool]$x = $true #
   [int]$n=$name.Length
   For([int]$i=0;($i -lt $n) -and $x;$i++)
   {
     if(($name[$i] -ge '0') -and ($name[$i] -le '9'))
     { 
      [string]$str=$name[$i]
      $i++
      while(($name[$i] -ge '0') -and ($name[$i] -le '9') -and ($i -lt $n) )
      {
        $str=$str+$name[$i]
        $i++
      }
      [int]$t=[int]::Parse($str)
      if($t -lt $num)
      {
      $x=$false #
      } 
     }
   }
   return !($x)
 }
 If( Func($_.BaseName) ) {Copy-Item ($_.FullName) -Destination $test}
}