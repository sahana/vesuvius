package org.damage.db;

public interface DBConstants {

    public interface SQL {
        public static final String SELECT = "select";
    }

    public interface Tables {
        //house related tables
        public static final String HOUSE = "house";
        public static final String HOUSE_DAMAGE_MOREINFO = "house_damage_moreinfo";
        public static final String HOUSE_FACILITY_INFO = "house_facility_info";

        //school related tables.
        public static final String SCHOOL = "school";
        public static final String SCHOOL_FACILITY_INFO = "school_facility_info";

    }

    public interface TableColumns {
        //house table
        public static final String ID = "Id";
        public static final String DISTRICT_CODE = "DistrictCode";
        public static final String DIVISION = "Division";
        public static final String GSN = "GSN";
        public static final String OWNER = "Owner";
        public static final String DISTANCE_FROM_SEA = "DistanceFromSea";
        public static final String CITY = "City";
        public static final String NO_AND_STREET = "NoAndStreet";
        public static final String CURRENT_ADDRESS = "CurrentAddress";
        public static final String FLOOR_AREA = "FloorArea";
        public static final String NO_OF_STORIES = "NoOfStories";
        public static final String TYPE_OF_OWNERSHIP = "TypeOfOwnership";
        public static final String NO_OF_RESIDENTS = "NoOfResidents";
        public static final String TYPE_OF_CONSTRUCTION = "TypeOfConstruction";
        public static final String PROPERTY_TAX_NO = "PropertyTaxNo";
        public static final String TOTAL_DAMAGED_COST = "TotalDamageCost";
        public static final String LAND_AREA = "LandArea";
        public static final String RELOCATE = "Relocate";
        public static final String INSURED = "Insured";
        public static final String DAMAGED_TYPE = "DamageType";
        public static final String COMMENTS = "Comments";

        //house_damage_moreinfo table
        public static final String HOUSE_ID = "HouseId";
        public static final String DAMAGE_INFO = "DamageInfo";

        //house_facility_info table
        public static final String FACILITY_NAME = "FacilityName";
        public static final String DESCRIPTION = "Description";

        //school table
        public static final String NAME = "Name";
        public static final String PERMANENT_ADDRESS = "PermanentAddress";
        public static final String NO_OF_STUDENTS = "NoOfStudents";
        public static final String NO_OF_TEACHERS = "NoOfTeachers";
        public static final String NO_OF_GRADES = "NoOfGrades";
        public static final String NO_OF_CLASS_ROOMS = "NoOfClassRooms";
        public static final String NO_OF_DAMGED_CLASS_ROOMS = "NoOfDamagedClassRooms";
        public static final String OTHER_DAMAGES = "OtherDamages";

        //school_facility_info table
        public static final String SCHOOL_ID = "SchoolId";
        //public static final String FACILITY_NAME="FacilityName";
        //public static final String DESCRIPTION="Description";
    }

}
