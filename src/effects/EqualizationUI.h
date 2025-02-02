/**********************************************************************

  Audacity: A Digital Audio Editor

  EqualizationUI.h

  Mitch Golden
  Vaughan Johnson (Preview)

  Paul Licameli split from Equalization.h

***********************************************************************/
#ifndef __AUDACITY_EFFECT_EQUALIZATION_UI__
#define __AUDACITY_EFFECT_EQUALIZATION_UI__

#include "EffectPlugin.h"
#include "EqualizationBandSliders.h"

class wxButton;
class wxCheckBox;
class wxChoice;
class wxRadioButton;
class wxSizer;
class wxSizerItem;
class wxStaticText;
class EqualizationPanel;
class RulerPanel;

#include <wx/weakref.h>

class EqualizationUI : public wxEvtHandler {
public:
   EqualizationUI(EffectSettingsManager &manager,
      const wxWeakRef<wxWindow> &uiParent,
      const TranslatableString &name, EqualizationCurvesList &curvesList,
      int options
   )  : mManager{ manager }
      , mUIParent{ uiParent }
      , mName{ name }
      , mCurvesList{ curvesList }
      , mOptions{ options }
   {}

   bool ValidateUI(EffectSettings &settings);
   void Init() { mBands.Init(); }
   void setCurve(int currentCurve);
   void setCurve(const wxString &curveName);
   std::unique_ptr<EffectUIValidator> PopulateOrExchange(
      ShuttleGui & S, EffectInstance &instance,
      EffectSettingsAccess &access, const EffectOutputs *pOutputs);
   bool TransferDataToWindow(const EffectSettings &settings);

private:
   // Convenience function template for binding event handler functions
   template<typename EventTag, typename Class, typename Event>
   void BindTo(
      wxEvtHandler &src, const EventTag& eventType, void (Class::*pmf)(Event &))
   {
      src.Bind(eventType, pmf, static_cast<Class *>(this));
   }

   void UpdateCurves();
   void UpdateRuler();
   void UpdateDraw();
   void UpdateGraphic();

   void OnSize( wxSizeEvent & event );
   void OnInterp( wxCommandEvent & event );
   void OnSliderM( wxCommandEvent & event );
   void OnSliderDBMAX( wxCommandEvent & event );
   void OnSliderDBMIN( wxCommandEvent & event );
   void OnDrawMode( wxCommandEvent &event );
   void OnGraphicMode( wxCommandEvent &event );
   void OnCurve( wxCommandEvent & event );
   void OnManage( wxCommandEvent & event );
   void OnClear( wxCommandEvent & event );
   void OnInvert( wxCommandEvent & event );
   void OnGridOnOff( wxCommandEvent & event );
   void OnLinFreq( wxCommandEvent & event );
   void OnIdle( wxIdleEvent &event );

   void setCurve();

   EffectSettingsManager &mManager;
   const wxWeakRef<wxWindow> &mUIParent;
   EqualizationCurvesList &mCurvesList;
   TranslatableString mName;
   const int mOptions;

   RulerPanel *mdBRuler;
   RulerPanel *mFreqRuler;

   bool mDisallowCustom{ false };

   wxSizer *szrC;
   wxSizer *szrG;
   wxSizer *szrV;
   wxSizer *szrH;
   wxSizer *szrI;
   wxSizer *szrL;
   wxSizer *szr1;
   wxSizer *szr2;
   wxSizer *szr3;
   wxSizer *szr4;
   wxSizer *szr5;

   wxSizerItem *mLeftSpacer;

   wxWeakRef<EqualizationPanel> mPanel{};
   //wxPanel *mGraphicPanel;
   wxRadioButton *mDraw{};
   wxRadioButton *mGraphic{};
   wxCheckBox *mLinFreq;
   wxCheckBox *mGridOnOff;
   wxChoice *mInterpChoice;
   wxWeakRef<wxChoice> mCurve{};
   wxButton *mManage;
   wxStaticText *mMText;
   wxSlider *mMSlider{};
   wxSlider *mdBMinSlider;
   wxSlider *mdBMaxSlider;
   EqualizationBandSliders mBands{ mCurvesList };

   DECLARE_EVENT_TABLE()
};
#endif
