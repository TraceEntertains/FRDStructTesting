#include "main.h"

template <size_t size>
std::string ConvertMacAddressToString(std::array<u8, size> &macAddress) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (int i = 0; i < 6; ++i) {
        ss << std::setw(2) << static_cast<unsigned>(macAddress[i]);
        if (i < 5) {
            ss << ':';
        }
    }

    return ss.str();
}

template <size_t size>
std::string ConvertU16ArrayToString(std::array<u16, size> u16Array) {
    std::string result;
    std::size_t length = 0;
    while (u16Array[length] != 0) {
        char lowerByte = static_cast<char>(u16Array[length] & 0xFF);
        result += lowerByte;
        length++;
    }
    return result;
}

u16 ChecksummedMiiData::CalcChecksum() {
    // Calculate the checksum of the selected Mii, see https://www.3dbrew.org/wiki/Mii#Checksum
    return boost::crc<16, 0x1021, 0, 0, false, false>(this, offsetof(ChecksummedMiiData, crc16));
}

int CalculateCheckDigit(const std::string& serialNumber) {
    int oddSum = 0, evenSum = 0;
    bool even = false;
    for (int i = 2; i < 10; i++) {
        if (even)
            evenSum += serialNumber[i] - '0';
        else
            oddSum += serialNumber[i] - '0';

        even = !even;
    }

    // Apply the formula
    int algResult = ((3 * evenSum) + oddSum) % 10;

    // Calculate the check digit
    int checkDigit = (algResult != 0) ? (10 - algResult) : 0;

    return checkDigit;
}

void WriteMiiData(ChecksummedMiiData mii) {
    std::cout << "magic: " << static_cast<unsigned>(mii.mii_data.magic) << '\n';

    std::cout << "\n\n" << "mii_options: " << "\n";
    std::cout << "allow_copying: " << static_cast<unsigned>(mii.mii_data.mii_options.allow_copying) << '\n';
    std::cout << "is_private_name: " << static_cast<unsigned>(mii.mii_data.mii_options.is_private_name) << '\n';
    std::cout << "region_lock: " << static_cast<unsigned>(mii.mii_data.mii_options.region_lock) << '\n';
    std::cout << "char_set: " << static_cast<unsigned>(mii.mii_data.mii_options.char_set) << '\n';

    std::cout << "\n\n" << "mii_pos: " << "\n";
    std::cout << "page_index: " << static_cast<unsigned>(mii.mii_data.mii_pos.page_index) << '\n';
    std::cout << "slot_index: " << static_cast<unsigned>(mii.mii_data.mii_pos.slot_index) << '\n';

    std::cout << "\n\n" << "console_identity: " << "\n";
    std::cout << "unknown0: " << static_cast<unsigned>(mii.mii_data.console_identity.unknown0) << '\n';
    std::cout << "origin_console: " << static_cast<unsigned>(mii.mii_data.console_identity.origin_console) << '\n';

    //std::cout << "system_id: " << mii.mii_data.system_id << '\n';
    //std::cout << "mii_id: " << mii.mii_data.mii_id << '\n';
    std::cout << "mac: " << ConvertMacAddressToString(mii.mii_data.mac) << '\n';
    std::cout << "pad: " << static_cast<unsigned>(mii.mii_data.pad) << '\n';

    std::cout << "\n\n" << "mii_details: " << "\n";
    std::cout << "gender (0 = male, 1 = female): " << static_cast<unsigned>(mii.mii_data.mii_details.sex) << '\n';
    std::cout << "bday_month: " << static_cast<unsigned>(mii.mii_data.mii_details.bday_month) << '\n';
    std::cout << "bday_day: " << static_cast<unsigned>(mii.mii_data.mii_details.bday_day) << '\n';
    std::cout << "shirt_color: " << static_cast<unsigned>(mii.mii_data.mii_details.shirt_color) << '\n';
    std::cout << "favorite: " << static_cast<unsigned>(mii.mii_data.mii_details.favorite) << '\n';

    std::cout << "mii_name: " << ConvertU16ArrayToString(mii.mii_data.mii_name) << '\n';
    std::cout << "height: " << static_cast<unsigned>(mii.mii_data.height) << '\n';
    std::cout << "width: " << static_cast<unsigned>(mii.mii_data.width) << '\n';

    std::cout << "\n\n" << "face_style: " << "\n";
    std::cout << "disable_sharing: " << static_cast<unsigned>(mii.mii_data.face_style.disable_sharing) << '\n';
    std::cout << "shape: " << static_cast<unsigned>(mii.mii_data.face_style.shape) << '\n';
    std::cout << "skin_color: " << static_cast<unsigned>(mii.mii_data.face_style.skin_color) << '\n';
    std::cout << "wrinkles: " << static_cast<unsigned>(mii.mii_data.face_details.wrinkles) << '\n';
    std::cout << "makeup: " << static_cast<unsigned>(mii.mii_data.face_details.makeup) << '\n';

    std::cout << "hair_style: " << static_cast<unsigned>(mii.mii_data.hair_style) << '\n';

    std::cout << "\n\n" << "hair_details: " << "\n";
    std::cout << "color: " << static_cast<unsigned>(mii.mii_data.hair_details.color) << '\n';
    std::cout << "flip: " << static_cast<unsigned>(mii.mii_data.hair_details.flip) << '\n';

    std::cout << "\n\n" << "eye_details: " << "\n";
    std::cout << "style: " << static_cast<unsigned>(mii.mii_data.eye_details.style) << '\n';
    std::cout << "color: " << static_cast<unsigned>(mii.mii_data.eye_details.color) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.eye_details.scale) << '\n';
    std::cout << "yscale: " << static_cast<unsigned>(mii.mii_data.eye_details.yscale) << '\n';
    std::cout << "rotation: " << static_cast<unsigned>(mii.mii_data.eye_details.rotation) << '\n';
    std::cout << "xspacing: " << static_cast<unsigned>(mii.mii_data.eye_details.xspacing) << '\n';
    std::cout << "yposition: " << static_cast<unsigned>(mii.mii_data.eye_details.yposition) << '\n';

    std::cout << "\n\n" << "eyebrow_details: " << "\n";
    std::cout << "style: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.style) << '\n';
    std::cout << "color: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.color) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.scale) << '\n';
    std::cout << "yscale: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.yscale) << '\n';
    std::cout << "pad: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.pad) << '\n';
    std::cout << "rotation: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.rotation) << '\n';
    std::cout << "xspacing: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.xspacing) << '\n';
    std::cout << "yposition: " << static_cast<unsigned>(mii.mii_data.eyebrow_details.yposition) << '\n';

    std::cout << "\n\n" << "nose_details: " << "\n";
    std::cout << "style: " << static_cast<unsigned>(mii.mii_data.nose_details.style) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.nose_details.scale) << '\n';
    std::cout << "yposition: " << static_cast<unsigned>(mii.mii_data.nose_details.yposition) << '\n';

    std::cout << "\n\n" << "mouth_details: " << "\n";
    std::cout << "style: " << static_cast<unsigned>(mii.mii_data.mouth_details.style) << '\n';
    std::cout << "color: " << static_cast<unsigned>(mii.mii_data.mouth_details.color) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.mouth_details.scale) << '\n';
    std::cout << "yscale: " << static_cast<unsigned>(mii.mii_data.mouth_details.yscale) << '\n';

    std::cout << "\n\n" << "mustache_details: " << "\n";
    std::cout << "mouth_yposition: " << static_cast<unsigned>(mii.mii_data.mustache_details.mouth_yposition) << '\n';
    std::cout << "mustache_style: " << static_cast<unsigned>(mii.mii_data.mustache_details.mustach_style) << '\n';
    std::cout << "pad: " << static_cast<unsigned>(mii.mii_data.mustache_details.pad) << '\n';

    std::cout << "\n\n" << "beard_details: " << "\n";
    std::cout << "style: " << static_cast<unsigned>(mii.mii_data.beard_details.style) << '\n';
    std::cout << "color: " << static_cast<unsigned>(mii.mii_data.beard_details.color) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.beard_details.scale) << '\n';
    std::cout << "ypos: " << static_cast<unsigned>(mii.mii_data.beard_details.ypos) << '\n';

    std::cout << "\n\n" << "glasses_details: " << "\n";
    std::cout << "style: " << static_cast<unsigned>(mii.mii_data.glasses_details.style) << '\n';
    std::cout << "color: " << static_cast<unsigned>(mii.mii_data.glasses_details.color) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.glasses_details.scale) << '\n';
    std::cout << "ypos: " << static_cast<unsigned>(mii.mii_data.glasses_details.ypos) << '\n';

    std::cout << "\n\n" << "mole_details: " << "\n";
    std::cout << "enable: " << static_cast<unsigned>(mii.mii_data.mole_details.enable) << '\n';
    std::cout << "scale: " << static_cast<unsigned>(mii.mii_data.mole_details.scale) << '\n';
    std::cout << "xpos: " << static_cast<unsigned>(mii.mii_data.mole_details.xpos) << '\n';
    std::cout << "ypos: " << static_cast<unsigned>(mii.mii_data.mole_details.ypos) << '\n';

    std::cout << "author_name: " << ConvertU16ArrayToString(mii.mii_data.author_name) << "\n\n" << "end of miidata" << "\n\n\n";
}

void MyDataTest() {
    FRDMyData obj;

    // Open the binary file for reading
    FILE* file = std::fopen("mydata", "rb");
    if (file) {
        // Read the binary data into the struct
        std::fread(&obj, sizeof(FRDMyData), 1, file);

        // Close the file
        std::fclose(file);

        // Print the data
        std::cout << "magic: " << obj.magic << std::endl;

        std::cout << "magic_number: " << obj.magic_number << std::endl;

        std::cout << "padding1: " << obj.padding1 << std::endl;

        std::cout << "unk10: ";
        for (const auto& value : obj.unk10) {
            std::cout << static_cast<unsigned>(value) << " ";
        }
        std::cout << std::endl;

        std::cout << "comment: ";
        for (const auto& value : obj.comment) {
            std::string str(reinterpret_cast<const char*>(&value));
            std::cout << str;
        }
        std::cout << std::endl;

        std::cout << "unk50: " << obj.unk50 << std::endl;

        // Print the values of the members in the FriendProfile struct

        std::cout << "local_friend_code_seed: " << obj.local_friend_code_seed << std::endl;

        std::cout << "unk68 (potentially password): ";
        std::string pass = ConvertU16ArrayToString(obj.unk68);
        std::cout << pass << std::endl;

        std::cout << "serial_number: ";
        std::string serial = ConvertU16ArrayToString(obj.serial_number);
        std::cout << serial << CalculateCheckDigit(serial) << std::endl;

        std::cout << "display_name: ";
        std::string display_name = ConvertU16ArrayToString(obj.display_name);
        std::cout << display_name << std::endl;

        std::cout << "padding2: ";
        for (const auto& value : obj.padding2) {
            std::cout << static_cast<unsigned>(value) << " ";
        }
        std::cout << std::endl;

        std::cout << "mii_data: " << std::endl; // Print the values of the members in the ChecksummedMiiData struct
        WriteMiiData(obj.mii_data);

        std::cout << "padding3: ";
        for (const auto& value : obj.padding3) {
            std::cout << static_cast<unsigned>(value) << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cerr << "Failed to open file." << std::endl;
    }
}

int main() {

    MyDataTest();
    return 0;
}