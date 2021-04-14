resolution = 25;

difference()
{
    cube(100, center = true);
    translate([50,50,50])
    { sphere(71, $fn=resolution); }
    translate([-50,50,50])
    { sphere(71, $fn=resolution); }
    translate([50,-50,50])
    { sphere(71, $fn=resolution); }
    translate([-50,-50,50])
    { sphere(71, $fn=resolution); }
    translate([50,50,-50])
    { sphere(71, $fn=resolution); }
    translate([-50,50,-50])
    { sphere(71, $fn=resolution); }
    translate([50,-50,-50])
    { sphere(71, $fn=resolution); }
    translate([-50,-50,-50])
    { sphere(71, $fn=resolution); }
}