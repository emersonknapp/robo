//cube(10, 10, 10);

eps = 0.5;

module nut(d, h) {
    r = d / 2.0;
    R = r * 2.0 / sqrt(3.0);
//    translate([R, R, 0]) 
    cylinder(h, R, R, $fn=6);
}
//nut(6, 3);

battery_length = 85.1;
battery_width = 77.4;
battery_height = 22.4;
module battery() {
    length = 85.1;
    width = 77.4;
    height = 22.4;
    radius = height / 2.0;
    
    translate([0, radius, radius])
    rotate([0, 90, 0])
        hull() {
            cylinder(length, radius, radius, $fn=100);
            translate([0, width - height, 0]) cylinder(length, radius, radius, $fn=100);
        }
    buff = 7;
    diff = 15;
    translate([0, 0, -10]) {
    translate([buff, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*1, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*2, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*3, radius, 0]) cube([10, width - height, 40]);
    translate([buff+diff*4, radius, 0]) cube([10, width - height, 40]);
    }
}


pmm_width = 50.0;
pmm_length = 60.0;
pmm_height = 15.0;

module pmm_base() {
    width = pmm_width;
    length = pmm_length;
    height = pmm_height;
    // base
    cube([width, length, height]);
    // battery-side space
    translate([-3, -1, 0]) cube([4, length + 5, height+2]);
    // cable space
    translate([0, length-1, 2]) cube([width+1, 20, height+2]);
    // far-side space
    translate([width, -1, 0])  cube([1, length, height+2]);
    // back space
    translate([0, -1, 0]) cube([width, 2, height+2]);

}

module pmm() {
    hh = 4;
    ho = 4.1;
    hole = 1.7;
    ll = 52.25;
    nw = 5.6;
    nh = 5.0;
    od = 4;
    ph = 30;
    sw = 41.5;
    sl = 44.5;

    difference() {
        translate([0, 0, 0]) pmm_base();
        // hole standoffs
        translate([4.1, 4.1, 0]) {
            translate([00, 00, -1]) cylinder(hh, od, od, $fn=50);
            translate([00, sl, -1]) cylinder(hh, od, od, $fn=50);
            translate([sw, 00, -1]) cylinder(hh, od, od, $fn=50);
            translate([sw, ll, -1]) cylinder(hh, od, od, $fn=50);

        }
    }
    // bolt punchouts
    translate([ho, ho, -10]) {
        translate([00, 00, 0]) cylinder(ph, hole, hole, $fn=50);
        translate([00, sl, 0]) cylinder(ph, hole, hole, $fn=50);
        translate([sw, 00, 0]) cylinder(ph, hole, hole, $fn=50);
        translate([sw, ll, 0]) cylinder(ph, hole, hole, $fn=50);
    }
    // nut sinks
    translate([ho, ho, -3]) {
        translate([00, 00, 0]) nut(nw, nh);
        translate([00, sl, 0]) nut(nw, nh);
        translate([sw, 00, 0]) nut(nw, nh);
        translate([sw, ll, 0]) nut(nw, nh);
    }
    // ziptie punchouts
    translate([pmm_width-2, 15, -10]) {
        cube([2, 5, ph]);
        translate([0, 50, 0]) cube([2, 5, ph]);
    }
}

usb_width = 36.5;
usb_height = 4.0;
usb_length = 80.0;
module cp2112() {
    cube([usb_width, usb_length, usb_height+10]);
}

module usb_holder() {
    over = 2;
    difference() {
        cube([usb_width+over, usb_length+over, usb_height+1]);
        translate([1, 1, 1]) cp2112();
    }
}


module rrc_positive() {
  translate([0, 1, 0]) battery();
  translate([battery_length+2, 0, 0]) {
      pmm();
  }
}


module rrc_holder() {
    over = 3;
    block_height = 5.0;
    total = battery_length + pmm_width + 2 + over;
    difference() {   
        cube([total, battery_width+over, block_height]);
        translate([1, 1.5, 0.75]) rrc_positive();
    }
}

module robo_battery() {
    union() {
        rrc_holder();
        translate([battery_length+pmm_width+2+3, 0, 0]) usb_holder();
    }
}

//nut();
pmm();
//usb_holder();
//rrc_positive();
//rrc_holder();
//robo_battery();
