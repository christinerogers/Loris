/*global document: false, $: false, window: false, unescape: false, Option: false,isElementsSet*/


function isCNVElementSet() {
    "use strict";
    var set = 0,
        options = $('#cnv-options option:selected'),  //get all the selected dropdowns within div ID=cnv-options
        texts = $('#cnv-options input[type=text]');
    ///browse through the selected dropdowns
    ///if any of the dropdown is not equal to 'All' then set the variable set to true
    options.each(function () {
        var value = $(this).text();
        if (value !== 'All' && value !== 'Any') {
            set = 1;
            return;
        }
    });
    //browse though the text elements
    ///if any of the text element is not empty then set the variable set to true
    texts.each(function () {
        var value = $(this).val();
        if (value !== '') {
            set = 1;
            return;
        }
    });
    return set; 
}

function toggleCNV() {
    "use strict";
//    $(".CNVselector").toggle();
    $("#show-cnv-selector").toggle();
    $("#hide-cnv-selector").toggle();
    $("#cnv-options").toggle();
}

function showCNVoptionsCheck() {
    "use strict";
    var els = $('#cnv-options'),///get all the TR elements with the ID advancedOptions
        set = isCNVElementSet();
    if (set) {
        els.show();
        $("#show-cnv-selector").hide();
        $("#hide-cnv-selector").show();
    } else {
        $("#show-cnv-selector").show();
        els.hide();
    }
    //console.log("Set == " + set ); 
}

function isSNPElementSet() {
    "use strict";
    var set = 0,
        options = $('#snp-options option:selected'),  ///get all the selected dropdowns within div ID=snp-options
        texts = $('#snp-options input[type=text]');
    ///browse through the selected dropdowns
    ///if any of the dropdown is not equal to 'All' then set the variable set to true
    options.each(function () {
        var value = $(this).text();
        if (value !== 'All' && value !== 'Any') {
            set = 1;
            return;
        }
    });
    //browse though the text elements
    ///if any of the text element is not empty then set the variable set to true
    texts.each(function () {
        var value = $(this).val();
        if (value !== '') {
            set = 1;
            return;
        }
    });
    return set; 
}

function toggleSNP() {
    "use strict";
    //$(".SNPselector").toggle();
    $("#show-snp-selector").toggle();
    $("#hide-snp-selector").toggle();
    $("#snp-options").toggle();
}

function showSNPoptionsCheck() {
    "use strict";
    var els = $('#snp-options'), //get all divs with the class SNPoptions
        set = isSNPElementSet();
    if (set) {
        els.show();
        $("#show-snp-selector").hide();
        $("#hide-snp-selector").show();
    } else {
        $("#show-snp-selector").show();
        els.hide();
    }
    //console.log("Set == " + set ); 
}

$(function () {
    "use strict";
    showCNVoptionsCheck();
    showSNPoptionsCheck();

    $('input[name=dob]').datepicker({
        dateFormat: 'yy-mm-dd',
        changeMonth: true,
        changeYear: true
    });
});

$(document).ready(function(){
    $.getScript("js/modules/dynamic_table.table.js")
        .done(function(){
            Table.setup("content", "scrollRight", "scrollLeft");
            Table.checkOverflow("content", "scrollRight", "scrollLeft");
        });
    // checkOverflow();
});
$(window).resize(function(){
    Table.checkOverflow("content", "scrollRight", "scrollLeft");
    // checkOverflow();
});

