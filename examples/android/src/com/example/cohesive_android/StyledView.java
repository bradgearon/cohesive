package com.example.cohesive_android;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;

public class StyledView extends View {

    private int style;
    private Context context;

    public StyledView(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.context = context;
        style = attrs.getStyleAttribute();
    }

    public int getStyle() {
        return style;
    }

}
