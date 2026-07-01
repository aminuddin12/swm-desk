import QtQuick
import QtQuick.Layouts
import foundation
import theme

ColumnLayout {
    spacing: SWMSpacing.space16

    Text {
        text: "Heading 1 - Inter Variable"
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.h1
        font.weight: SWMTypography.weightBold
        color: ThemeEngine.textPrimary
    }
    
    Text {
        text: "Heading 2 - Inter Variable"
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.h2
        font.weight: SWMTypography.weightSemiBold
        color: ThemeEngine.textPrimary
    }
    
    Text {
        text: "Heading 3 - Inter Variable"
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.h3
        font.weight: SWMTypography.weightMedium
        color: ThemeEngine.textPrimary
    }
    
    Text {
        text: "Body Large - Standard text for spacious areas"
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.bodyLarge
        font.weight: SWMTypography.weightRegular
        color: ThemeEngine.textSecondary
    }
    
    Text {
        text: "Body Default - Primary readable text size"
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.body
        font.weight: SWMTypography.weightRegular
        color: ThemeEngine.textSecondary
    }
    
    Text {
        text: "Caption - Small descriptive text"
        font.family: SWMTypography.family
        font.pixelSize: SWMTypography.caption
        font.weight: SWMTypography.weightRegular
        color: ThemeEngine.textSecondary
    }
}
