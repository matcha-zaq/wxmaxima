//
//  Copyright (C) 2004-2014 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2012 Doug Ilijev <doug.ilijev@gmail.com>
//            (C) 2014-2015 Gunter Königsmann <wxMaxima@physikbuch.de>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef WXMAXIMAFRAME_H
#define WXMAXIMAFRAME_H

#include <wx/wx.h>

#include <wx/dirctrl.h>
#include <wx/listbox.h>
#include <wx/bmpbuttn.h>
#include <wx/arrstr.h>
#include <wx/aui/aui.h>

#include "MathCtrl.h"
#include "Setup.h"
#include "History.h"


/*! The frame containing the menu and the sidebars
 */
class wxMaximaFrame: public wxFrame
{
public:

  /*! A list of all events the maxima frame can receive

    This list serves several purposes:
     - wxwidgets uses this list to tell us what kind of events it has to inform us about.
     - we use these events for inter process communication.\n
       For example the "evaluate this cell" menu is clicked by the enter (or the shift+enter,
       depending on what option is set in the configuration).
     - Thirdly his enum is used for assigning panels an ID that matches the ID of the event
       that toggles them which makes the handling of these IDs easier.
   */
  enum Event{

    /*! Hide all panes
      
      This event is assigned an ID higher than the highest ID wxWidgets assigns to 
      its internal events in order to avoid ID clashes.
    */
    menu_pane_hideall = wxID_HIGHEST+1,
    /*! Both used as the "toggle the math pane" command and as the ID of the math pane

      Since this enum is also used for iterating over the panes it is vital 
      that this entry stays that of the first pane in this enum.
     */
    menu_pane_math,
    menu_pane_history,		//!< Both the "toggle the history pane" command and the history pane
    menu_pane_format,		//!< Both the "toggle the format pane" command and the format pane
    /*! Both used as the "toggle the stats pane" command and as the ID of the stats pane

      Since this enum is also used for iterating over the panes it is vital 
      that this entry stays that of the last pane in this enum.
     */
    menu_pane_stats,

    socket_client_id,
    socket_server_id,
    plot_slider_id,
    input_line_id,
    menu_new_id,
    menu_open_id,
    menu_batch_id,
    menu_save_id,
    menu_save_as_id,
    menu_load_id,
    menu_sconsole_id,
    menu_interrupt_id,
    menu_restart_id,
    menu_solve,
    menu_solve_to_poly,
    menu_solve_num,
    menu_allroots,
    menu_bfallroots,
    menu_realroots,
    menu_solve_lin,
    menu_solve_algsys,
    menu_eliminate,
    menu_solve_ode,
    menu_ivp_1,
    menu_ivp_2,
    menu_bvp,
    menu_gen_mat,
    menu_gen_mat_lambda,
    menu_enter_mat,
    menu_invert_mat,
    menu_cpoly,
    menu_determinant,
    menu_eigen,
    menu_eigvect,
    menu_fun_def,
    menu_adjoint_mat,
    menu_transpose,
    menu_map_mat,
    menu_ratsimp,
    menu_radsimp,
    menu_factor,
    menu_gfactor,
    menu_expand,
    menu_talg,
    menu_tellrat,
    menu_modulus,
    menu_trigsimp,
    menu_trigreduce,
    menu_trigexpand,
    menu_trigrat,
    menu_rectform,
    menu_polarform,
    menu_demoivre,
    menu_exponentialize,
    menu_num_out,
    menu_to_float,
    menu_to_bfloat,
    menu_to_numer,
    menu_set_precision,
    menu_functions,
    menu_variables,
    menu_clear_var,
    menu_clear_fun,
    menu_integrate,
    menu_risch,
    menu_laplace,
    menu_ilt,
    menu_continued_fraction,
    menu_gcd,
    menu_lcm,
    menu_divide,
    menu_partfrac,
    menu_sum,
    menu_limit,
    menu_lbfgs,
    menu_series,
    menu_pade,
    menu_map,
    menu_diff,
    menu_solve_de,
    menu_atvalue,
    menu_maximahelp,
    menu_example,
    menu_apropos,
    menu_product,
    menu_make_list,
    menu_apply,
    menu_time,
    menu_factsimp,
    menu_factcomb,
    menu_realpart,
    menu_imagpart,
    menu_subst,
    button_factor_id,
    button_solve,
    button_solve_ode,
    button_limit,
    button_taylor,
    button_expand,
    button_ratsimp,
    button_radcan,
    button_trigsimp,
    button_trigexpand,
    button_trigreduce,
    button_trigrat,
    button_integrate,
    button_diff,
    button_sum,
    button_product,
    button_button_constant,
    button_factor,
    button_subst,
    button_plot2,
    button_plot3,
    button_rectform,
    button_map,
    gp_plot2,
    gp_plot3,
    menu_display,
    menu_soft_restart,
    menu_plot_format,
    menu_build_info,
    menu_bug_report,
    menu_add_path,
    menu_evaluate_all_visible,
    menu_evaluate_all,
    menu_evaluate_till_here,
    menu_show_tip,
    menu_copy_from_console,
    menu_copy_tex_from_console,
    menu_copy_text_from_console,
    menu_undo,
    menu_redo,
    menu_select_all,
    menu_logcontract,
    menu_logexpand,
    menu_to_fact,
    menu_to_gamma,
    menu_texform,
    button_enter,
    menu_zoom_in,
    menu_zoom_out,
    menu_zoom_80,
    menu_zoom_100,
    menu_zoom_120,
    menu_zoom_150,
    menu_zoom_200,
    menu_zoom_300,
    menu_copy_as_bitmap,
    menu_copy_to_file,
    menu_export_html,
    menu_change_var,
    menu_nouns,
#if defined (__WXMSW__) || defined (__WXGTK20__) 
    tb_new,
#endif
#if defined (__WXMSW__) || defined (__WXGTK20__) || defined (__WXMAC__)
    tb_open,
    tb_save,
    tb_copy,
    tb_paste,
    tb_cut,
    tb_select_all,
    tb_print,
    tb_pref,
    tb_interrupt,
    tb_help,
    tb_animation_start,
    tb_animation_stop,
    tb_find,
#endif
    menu_evaluate,
    menu_add_comment,
    menu_add_subsection,
    menu_add_section,
    menu_add_title,
    menu_add_pagebreak,
    menu_fold_all_cells,
    menu_unfold_all_cells,
    menu_insert_input,
    menu_insert_previous_input,
    menu_insert_previous_output,
    menu_autocomplete,
    menu_autocomplete_templates,
    menu_cut,
    menu_paste,
    menu_paste_input,
    menu_fullscreen,
    menu_remove_output,
#if defined (__WXMAC__)
    mac_newId,
    mac_openId,
    mac_closeId,
#endif
    menu_recent_documents,
    menu_recent_document_0,
    menu_recent_document_1,
    menu_recent_document_2,
    menu_recent_document_3,
    menu_recent_document_4,
    menu_recent_document_5,
    menu_recent_document_6,
    menu_recent_document_7,
    menu_recent_document_8,
    menu_recent_document_9,
    menu_insert_image,
    menu_stats_mean,
    menu_stats_median,
    menu_stats_var,
    menu_stats_dev,
    menu_stats_tt1,
    menu_stats_tt2,
    menu_stats_tnorm,
    menu_stats_linreg,
    menu_stats_lsquares,
    menu_stats_histogram,
    menu_stats_scatterplot,
    menu_stats_barsplot,
    menu_stats_piechart,
    menu_stats_boxplot,
    menu_stats_readm,
    menu_stats_enterm,
    menu_stats_subsample,
    menu_format_code,
    menu_format_text,
    menu_format_subsection,
    menu_format_section,
    menu_format_title,
    menu_format_image,
    menu_format_pagebreak,
    menu_help_tutorials,
    menu_show_toolbar,
    menu_edit_find,
    menu_history_previous,
    menu_history_next,
    menu_check_updates
  };

 wxMaximaFrame(wxWindow* parent, int id, const wxString& title,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE);
  ~wxMaximaFrame();
  /*! Update the recent documents list

    Copies the string array containing the list of recent documents to the
    recent documents menu.
   */
  void UpdateRecentDocuments();
  //! Add an entry to the "Recent Documents" list.
  void AddRecentDocument(wxString file);
  /*! Remove a file from the "Recent Documents" list.

    Removing and re-adding a file will move it to the top of the list.
   */
  void RemoveRecentDocument(wxString file);
  //! Read the nth entry in the list of recent documents.
  wxString GetRecentDocument(int i) { return m_recentDocuments[i]; }
  /*! true, if a Pane is currently enabled

    \param id The event that toggles the visibility of the pane that is
    to be queried
   */
  bool IsPaneDisplayed(Event id);
  /*! Show or hide a sidebar
    
    \param id The type of the sidebar to show/hide
    \param hide 
     - true: show the sidebar
     - false: hide it
   */
  void ShowPane(Event id, bool hide);
  //! Adds a command to the list  of recently used maxima commands
  void AddToHistory(wxString cmd) { m_history->AddToHistory(cmd); }
  /*! Show or hide the toolbar

    \param show
     - true:  Thow the toolbar
     - false: hide the toolbar
   */
  void ShowToolBar(bool show);
private:
  //! The menu bar
  wxMenuBar *m_MenuBar;
  //! The file menu.
  wxMenu *m_FileMenu; 
  //! The edit menu.
  wxMenu *m_EditMenu; 
  //! The cell menu.
  wxMenu *m_CellMenu; 
  //! The zoom submenu
  wxMenu *m_Edit_Zoom_Sub;
  //! The panes submenu
  wxMenu *m_Maxima_Panes_Sub;
  //! The equations menu.
  wxMenu *m_EquationsMenu; 
  //! The maxima menu.
  wxMenu *m_MaximaMenu; 
  //! The algebra menu.
  wxMenu *m_Algebra_Menu;
  //! The simplify menu
  wxMenu *m_SimplifyMenu;
  //! The factorials and gamma submenu
  wxMenu *m_Simplify_Gamma_Sub;
  //! The trigonometric submenu
  wxMenu *m_Simplify_Trig_Sub;
  //! The complex submenu
  wxMenu *m_Simplify_Complex_Sub;
  //! The calculus menu
  wxMenu *m_CalculusMenu;
  //! The plot menu
  wxMenu *m_PlotMenu;
  //! The numeric menu
  wxMenu *m_NumericMenu;
  //! The help menu
  wxMenu *m_HelpMenu;
  
  void set_properties();
  void do_layout();
#if defined (__WXMSW__) || defined (__WXGTK20__) || defined (__WXMAC__)
  void SetupToolBar();
#endif
  void SetupMenu();
  wxPanel *CreateStatPane();
  wxPanel *CreateMathPane();
  wxPanel *CreateFormatPane();
protected:
  void LoadRecentDocuments();
  void SaveRecentDocuments();
  wxAuiManager m_manager;

  MathCtrl* m_console;
  History * m_history;
  wxSlider* m_plotSlider;
  wxArrayString m_recentDocuments;
  wxMenu* m_recentDocumentsMenu;
};

#endif // WXMAXIMAFRAME_H
