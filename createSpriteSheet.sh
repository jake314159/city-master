
# Where the temp image files are stored
mkdir images/temp



python sprite_line_maker.py images/temp/001_ground.png v images/001_ground/*.png
python sprite_line_maker.py images/temp/002_highlight.png v images/002_highlight/*.png
python sprite_line_maker.py images/temp/003_single_tile_buildings.png v images/003_single_tile_buildings/*.png
python sprite_line_maker.py images/temp/004_road.png v images/004_road/*.png
python sprite_line_maker.py images/temp/005_build_icons.png v images/005_build_icons/*.png
python sprite_line_maker.py images/temp/006_zone_residential_1.png v images/006_zone_residential_1/*.png
python sprite_line_maker.py images/temp/007_zone_residential_2.png v images/007_zone_residential_2/*.png

python sprite_line_maker.py images/tile_sheet.png h images/temp/*.png

rm -rdf images/temp
