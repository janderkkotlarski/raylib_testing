resolution = 1;

difference()
{
    cube(100, center = true);
    translate([50,50,50])
    { sphere(71); }
    translate([-50,50,50])
    { sphere(71); }
    translate([50,-50,50])
    { sphere(71); }
    translate([-50,-50,50])
    { sphere(71); }
    translate([50,50,-50])
    { sphere(71); }
    translate([-50,50,-50])
    { sphere(71); }
    translate([50,-50,-50])
    { sphere(71); }
    translate([-50,-50,-50])
    { sphere(71); }
}